#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "avrweather.h"
#include "exception.h"
#include "webconnect.h"
#include "currenttime.h"
#include "csvhelper.h"

using namespace std;

#define LOG_RXTX

PFRAME				_pFrameMem = NULL;
int					_size = 0;
uint8_t				_msgID = 0;

FrameManager::FrameManager() : FrameManager(FRAME_MEM_SIZE)
{
}

FrameManager::FrameManager(int size)
{
	if (_pFrameMem == NULL) {
		_size = size;

		_pFrameMem = (PFRAME)malloc(sizeof(FRAME) * _size);

		if (_pFrameMem == NULL) {
			throw new Exception("Failed to allocate frame memory.");
		}

		memset(_pFrameMem, 0, sizeof(FRAME) * _size);
	}
}

FrameManager::~FrameManager()
{
	free(_pFrameMem);
}

int FrameManager::getSize()
{
	return _size;
}

PFRAME FrameManager::allocFrame()
{
	PFRAME 		frame = NULL;
	int			i;

	for (i = 0;i < _size;i++) {
		if (!_pFrameMem[i].isAllocated) {
			frame = &_pFrameMem[i];
			frame->isAllocated = 1;
			break;
		}
	}

	return frame;
}

void FrameManager::freeFrame(PFRAME pFrame)
{
	memset(pFrame, 0, sizeof(FRAME));
}


uint8_t getMsgID()
{
	uint8_t			msgID;

	msgID = _msgID++;

	return msgID;
}

int processFrame(PRXMSGSTRUCT pMsg, uint8_t * buffer, int bufferLength)
{
	int 				state = RX_STATE_START;
	int					i = 0;
	int					rtn = 0;
	int					count = 0;
	uint8_t				b;

	CurrentTime & time = CurrentTime::getInstance();

	pMsg->timeStamp = time.updateTime();

	while (count < bufferLength) {
		b = buffer[count++];

		switch (state) {
			case RX_STATE_START:
#ifdef LOG_RXTX
				printf("[S]");
				printf("[0x%02X]", b);
#endif
				if (b == MSG_CHAR_START) {
					pMsg->frame.start = b;
					state = RX_STATE_LENGTH;
				}
				break;

			case RX_STATE_LENGTH:
#ifdef LOG_RXTX
				printf("[L]");
				printf("[%d]", b);
#endif
				pMsg->frame.frameLength = b;
				state = RX_STATE_MSGID;
				break;

			case RX_STATE_MSGID:
#ifdef LOG_RXTX
				printf("[M]");
				printf("[0x%02X]", b);
#endif
				pMsg->frame.msgID = b;
				pMsg->frameChecksumTotal = b;
				state = RX_STATE_RESPONSE;
				break;

			case RX_STATE_RESPONSE:
#ifdef LOG_RXTX
				printf("[R]");
				printf("[0x%02X]", b);
#endif
				pMsg->frame.response = b;
				pMsg->frameChecksumTotal += b;
				state = RX_STATE_RESPTYPE;
				break;

			case RX_STATE_RESPTYPE:
				if (b == MSG_CHAR_ACK) {
#ifdef LOG_RXTX
					printf("[ACK]");
#endif
					pMsg->frame.responseType = MSG_CHAR_ACK;

					if (pMsg->frame.frameLength > 3) {
						state = RX_STATE_DATA;
						i = 0;
					}
					else {
						state = RX_STATE_CHECKSUM;
					}
				}
				else if (b == MSG_CHAR_NAK) {
#ifdef LOG_RXTX
					printf("[NAK]");
#endif
					pMsg->frame.responseType = MSG_CHAR_NAK;

					state = RX_STATE_ERRCODE;
				}

				pMsg->frameChecksumTotal += b;
				break;

			case RX_STATE_DATA:
#ifdef LOG_RXTX
				printf("%c", b);
#endif
				pMsg->frame.data[i++] = b;
				pMsg->frameChecksumTotal += b;

				if (i == pMsg->frame.frameLength - 2) {
					state = RX_STATE_CHECKSUM;
				}
				break;

			case RX_STATE_ERRCODE:
#ifdef LOG_RXTX
				printf("[E]");
				printf("[0x%02X]", b);
#endif
				pMsg->frame.errorCode = b;
				pMsg->frameChecksumTotal += b;
				state = RX_STATE_CHECKSUM;
				break;

			case RX_STATE_CHECKSUM:
#ifdef LOG_RXTX
				printf("[C]");
				printf("[0x%02X]", b);
#endif
				pMsg->frame.checksum = b;
				pMsg->frameChecksumTotal += b;

				/*
				 * Validate the checksum...
				 */
				if ((pMsg->frameChecksumTotal & 0x00FF) != 0x00FF) {
					printf("ERROR: Invalid checksum [0x%02X]\n", pMsg->frame.checksum);
				}

				state = RX_STATE_END;
				break;

			case RX_STATE_END:
#ifdef LOG_RXTX
				printf("[N]");
				printf("[0x%02X]", b);
#endif
				if (b == MSG_CHAR_END) {
					pMsg->frame.end = b;
					rtn = 0;
#ifdef LOG_RXTX
					printf("\n");
#endif
				}

				state = RX_STATE_START;
				break;
		}
	}

	return rtn;
}

void processResponse(uint8_t * response, int responseLength)
{
	RXMSGSTRUCT			msg;
	char				szTPH[80];
	char				szCPU[8];
	char 				szTemperature[20];
	char 				szPressure[20];
	char 				szHumidity[20];
	char				szTimeStamp[20];
	static int			avgCount = 0;
	static bool			avgSave = true;
	static bool			minSave = false;
	static bool			maxSave = false;

	WebConnector & web = WebConnector::getInstance();

	CurrentTime & time = CurrentTime::getInstance();

	processFrame(&msg, response, responseLength);

	time.updateTime(&(msg.timeStamp));

	switch (msg.frame.response) {
		case RX_RSP_AVG_TPH:
			memcpy(szTPH, msg.frame.data, msg.frame.frameLength - 3);

			strcpy(szTemperature, strtok(szTPH, ";"));
			strcpy(szPressure, strtok(NULL, ";"));
			strcpy(szHumidity, strtok(NULL, ";"));

			try {
				web.postAvgTPH(avgSave, &szTemperature[2], &szPressure[2], &szHumidity[2]);

				avgCount++;

				/*
				 * Save once an hour...
				 */
				if (avgCount < 180) {
					avgSave = false;
				}
				else {
					avgSave = true;
					avgCount = 0;
				}
			}
			catch (Exception * e) {
				cout << "Caught exception posting to web server: " << e->getMessage() << endl;
				cout << "Writing to local CSV instead" << endl;

				sprintf(
					szTimeStamp,
					"%d-%02d-%02d %02d:%02d:%02d",
					time.getYear(),
					time.getMonth(),
					time.getDay(),
					time.getHour(),
					time.getMinute(),
					time.getSecond());

				vector<string> avgRecord = {szTimeStamp, "AVG", &szTemperature[2], &szPressure[2], &szHumidity[2]};

				CSVHelper & csvAvg = CSVHelper::getInstance();

				csvAvg.writeRecord(5, avgRecord);
			}
			break;

		case RX_RSP_MAX_TPH:
			memcpy(szTPH, msg.frame.data, msg.frame.frameLength - 3);

			strcpy(szTemperature, strtok(szTPH, ";"));
			strcpy(szPressure, strtok(NULL, ";"));
			strcpy(szHumidity, strtok(NULL, ";"));

			try {
				if (time.getHour() == 23 && time.getMinute() == 59 && time.getSecond() >= 30) {
					maxSave = true;
				}

				web.postMaxTPH(maxSave, &szTemperature[2], &szPressure[2], &szHumidity[2]);

				maxSave = false;
			}
			catch (Exception * e) {
				cout << "Caught exception posting to web server: " << e->getMessage() << endl;
				cout << "Writing to local CSV instead" << endl;

				sprintf(
					szTimeStamp,
					"%d-%02d-%02d %02d:%02d:%02d",
					time.getYear(),
					time.getMonth(),
					time.getDay(),
					time.getHour(),
					time.getMinute(),
					time.getSecond());

				vector<string> maxRecord = {szTimeStamp, "MAX", &szTemperature[2], &szPressure[2], &szHumidity[2]};

				CSVHelper & csvMax = CSVHelper::getInstance();

				csvMax.writeRecord(5, maxRecord);
			}
			break;

		case RX_RSP_MIN_TPH:
			memcpy(szTPH, msg.frame.data, msg.frame.frameLength - 3);

			strcpy(szTemperature, strtok(szTPH, ";"));
			strcpy(szPressure, strtok(NULL, ";"));
			strcpy(szHumidity, strtok(NULL, ";"));

			try {
				if (time.getHour() == 23 && time.getMinute() == 59 && time.getSecond() >= 30) {
					minSave = true;
				}

				web.postMinTPH(minSave, &szTemperature[2], &szPressure[2], &szHumidity[2]);

				minSave = false;
			}
			catch (Exception * e) {
				cout << "Caught exception posting to web server: " << e->getMessage() << endl;
				cout << "Writing to local CSV instead" << endl;

				sprintf(
					szTimeStamp,
					"%d-%02d-%02d %02d:%02d:%02d",
					time.getYear(),
					time.getMonth(),
					time.getDay(),
					time.getHour(),
					time.getMinute(),
					time.getSecond());

				vector<string> minRecord = {szTimeStamp, "MIN", &szTemperature[2], &szPressure[2], &szHumidity[2]};

				CSVHelper & csvMin = CSVHelper::getInstance();

				csvMin.writeRecord(5, minRecord);
			}
			break;

		case RX_RSP_RESET_MINMAX_TPH:
			break;

		case RX_RSP_ANEMOMETER:
			break;

		case RX_RSP_RAINGUAGE:
			break;

		case RX_RSP_PING:
			memcpy(szCPU, msg.frame.data, msg.frame.frameLength - 3);
			szCPU[msg.frame.frameLength - 3] = 0;
#ifdef LOG_RXTX
			cout << "CPU = " << szCPU << "%" << endl;
#endif
			break;
	}
}
