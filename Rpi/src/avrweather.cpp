#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "avrweather.h"
#include "exception.h"

#define LOG_RXTX

PFRAME				_pFrameMem = NULL;
int					_size = 0;
uint8_t				_msgID = 0;

FrameManager::FrameManager() : FrameManager(16)
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

	pMsg->timeStamp = time(0);

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
					printf("[ACK]");
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
					printf("[NAK]");
					pMsg->frame.responseType = MSG_CHAR_NAK;

					state = RX_STATE_ERRCODE;
				}

				pMsg->frameChecksumTotal += b;
				break;

			case RX_STATE_DATA:
				printf("%c", b);
				pMsg->frame.data[i++] = b;
				pMsg->frameChecksumTotal += b;

				if (i == pMsg->frame.frameLength - 2) {
					state = RX_STATE_CHECKSUM;
				}
				break;

			case RX_STATE_ERRCODE:
				printf("[E]");
				printf("[0x%02X]", b);
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
					printf("\n");
				}

				state = RX_STATE_START;
				break;
		}
	}

	return rtn;
}

void processResponse(FILE * fptr, uint8_t * response, int responseLength)
{
	RXMSGSTRUCT			msg;
	char				szTPH[80];
	char 				szTemperature[20];
	char 				szPressure[20];
	char 				szHumidity[20];
	struct tm *			time;

	processFrame(&msg, response, responseLength);

	switch (msg.frame.response) {
		case RX_RSP_AVG_TPH:
			time = localtime(&(msg.timeStamp));

			memcpy(szTPH, msg.frame.data, msg.frame.frameLength - 3);

			strcpy(szTemperature, strtok(szTPH, ";"));
			strcpy(szPressure, strtok(NULL, ";"));
			strcpy(szHumidity, strtok(NULL, ";"));

			fprintf(
				fptr,
				"%d-%02d-%02d %02d:%02d:%02d,AVG,%s,%s,%s\n",
				time->tm_year + 1900,
				time->tm_mon + 1,
				time->tm_mday,
				time->tm_hour,
				time->tm_min,
				time->tm_sec,
				&szTemperature[2],
				&szPressure[2],
				&szHumidity[2]);

			fflush(fptr);
			break;

		case RX_RSP_MAX_TPH:
			time = localtime(&(msg.timeStamp));

			memcpy(szTPH, msg.frame.data, msg.frame.frameLength - 3);

			strcpy(szTemperature, strtok(szTPH, ";"));
			strcpy(szPressure, strtok(NULL, ";"));
			strcpy(szHumidity, strtok(NULL, ";"));

			fprintf(
				fptr,
				"%d-%02d-%02d %02d:%02d:%02d,MAX,%s,%s,%s\n",
				time->tm_year + 1900,
				time->tm_mon + 1,
				time->tm_mday,
				time->tm_hour,
				time->tm_min,
				time->tm_sec,
				&szTemperature[2],
				&szPressure[2],
				&szHumidity[2]);

			fflush(fptr);
			break;

		case RX_RSP_MIN_TPH:
			time = localtime(&(msg.timeStamp));

			memcpy(szTPH, msg.frame.data, msg.frame.frameLength - 3);

			strcpy(szTemperature, strtok(szTPH, ";"));
			strcpy(szPressure, strtok(NULL, ";"));
			strcpy(szHumidity, strtok(NULL, ";"));

			fprintf(
				fptr,
				"%d-%02d-%02d %02d:%02d:%02d,MIN,%s,%s,%s\n",
				time->tm_year + 1900,
				time->tm_mon + 1,
				time->tm_mday,
				time->tm_hour,
				time->tm_min,
				time->tm_sec,
				&szTemperature[2],
				&szPressure[2],
				&szHumidity[2]);

			fflush(fptr);
			break;

		case RX_RSP_RESET_MINMAX_TPH:
			break;

		case RX_RSP_ANEMOMETER:
			break;

		case RX_RSP_RAINGUAGE:
			break;

		case RX_RSP_PING:
			break;
	}
}
