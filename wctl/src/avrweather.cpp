#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern "C" {
#include <gpioc.h>
}

#include "avrweather.h"
#include "queuemgr.h"
#include "exception.h"
#include "webconnect.h"
#include "currenttime.h"
#include "csvhelper.h"

using namespace std;

#define AVG_MSGS_PER_MIN			3

#define LOG_RXTX

uint8_t				_msgID = 0;

Frame::Frame()
{
	this->isAllocated = true;
}

void Frame::initialise(uint8_t * frame, int frameLength)
{
	this->buffer = frame;
	this->frameLength = frameLength;
}

uint8_t Frame::getMsgID()
{
	uint8_t	msgID;

	msgID = _msgID++;

	return msgID;
}

bool Frame::getIsAllocated()
{
	return isAllocated;
}

uint8_t * Frame::getData()
{
	if (this->getDataLength() == 0) {
		return NULL;
	}

	return &(this->buffer[4]);
}

int Frame::getDataLength()
{
	return this->frameLength - NUM_REQUEST_FRAME_BYTES;
}

uint8_t * Frame::getFrame()
{
	return this->buffer;
}

uint8_t Frame::getFrameByteAt(int index)
{
	if (index < 0 || index > this->frameLength - 1) {
		throw new Exception("Invalid index argument");
	}

	return this->buffer[index];
}

int Frame::getFrameLength()
{
	return this->frameLength;
}

uint8_t Frame::getLength()
{
	return this->getFrameByteAt(1);
}

uint8_t Frame::getMessageID()
{
	return this->getFrameByteAt(2);
}

uint8_t Frame::getChecksum()
{
	return this->getFrameByteAt(5 + this->getDataLength());
}

TxFrame::TxFrame(uint8_t * data, int dataLength, uint8_t cmdCode) : Frame()
{
	int				i;
	int				checksumTotal = 0;
	int				frameLength;

	frameLength = NUM_REQUEST_FRAME_BYTES + dataLength;

	frame = (uint8_t *)malloc(frameLength);

	if (frame == NULL) {
		throw new Exception("Cannot allocate frame memory.");
	}

	frame[0] = MSG_CHAR_START;
	frame[1] = 2 + dataLength;
	frame[2] = getMsgID();
	frame[3] = cmdCode;

	checksumTotal = (int)frame[2] + (int)frame[3];

	for (i = 0;i < dataLength;i++) {
		frame[i + 4] = data[i];
		checksumTotal += frame[i + 4];
	}

	frame[4 + dataLength] = (uint8_t)(0x00FF - (checksumTotal & 0x00FF));
	frame[5 + dataLength] = MSG_CHAR_END;

	initialise(frame, frameLength);
}

TxFrame::~TxFrame()
{
	free(frame);
}

uint8_t TxFrame::getCmdCode()
{
	return this->getFrameByteAt(3);
}

RxFrame::RxFrame(uint8_t * frame, int frameLength) : Frame()
{
	initialise(frame, frameLength);
}

uint8_t RxFrame::getResponseCode()
{
	return this->getFrameByteAt(3);
}

bool RxFrame::isACK()
{
	return (this->getFrameByteAt(4) == MSG_CHAR_ACK ? true : false);
}

bool RxFrame::isNAK()
{
	return (this->getFrameByteAt(4) == MSG_CHAR_NAK ? true : false);
}

bool RxFrame::isChecksumValid()
{
	int			i;
	uint16_t	checksumTotal = 0;

	for (i = 2;i < getFrameLength() - 1;i++) {
		checksumTotal += getFrame()[i];
	}

	return ((checksumTotal & 0x00FF) == 0x00FF ? true : false);
}

uint8_t RxFrame::getErrorCode()
{
	return this->getFrameByteAt(5);
}

uint8_t * RxFrame::getData()
{
	if (this->isACK()) {
		return &(this->getFrame()[5]);
	}
	else {
		return NULL;
	}
}

int RxFrame::getDataLength()
{
	if (this->isACK()) {
		return this->getFrameLength() - NUM_ACK_RSP_FRAME_BYTES;
	}
	else {
		return 0;
	}
}

void resetAVR()
{
#ifdef __arm__
	int		rc = 0;
	int		pin = AVR_RESET_PIN;

    rc = gpioc_open();

    if (rc == 0) {
        gpioc_setPinOutput(pin);

        gpioc_setPinOff(pin);
        usleep(100000);
        gpioc_setPinOn(pin);

        gpioc_close();
    }
#endif
}

RxFrame * send_receive(TxFrame * pTxFrame)
{
	QueueMgr & mgr = QueueMgr::getInstance();

	mgr.pushTx(pTxFrame);

	while (mgr.isRxQueueEmpty()) {
		usleep(100000L);
	}

	RxFrame * pRxFrame = mgr.popRx();

	return pRxFrame;
}

void printFrame(uint8_t * buffer, int bufferLength)
{
	int 				state = RX_STATE_START;
	int					i = 0;
	int					count = 0;
	uint8_t				b;

	printf("RX[%d]: ", bufferLength);
	for (i = 0;i < bufferLength;i++) {
		printf("[0x%02X]", buffer[i]);
	}
	printf("\n");

	while (count < bufferLength) {
		b = buffer[count++];

		switch (state) {
			case RX_STATE_START:
				printf("[S]");
				printf("[0x%02X]", b);

				if (b == MSG_CHAR_START) {
					state = RX_STATE_LENGTH;
				}
				break;

			case RX_STATE_LENGTH:
				printf("[L]");
				printf("[%d]", b);

				state = RX_STATE_MSGID;
				break;

			case RX_STATE_MSGID:
				printf("[M]");
				printf("[0x%02X]", b);

				state = RX_STATE_RESPONSE;
				break;

			case RX_STATE_RESPONSE:
				printf("[R]");
				printf("[0x%02X]", b);

				state = RX_STATE_RESPTYPE;
				break;

			case RX_STATE_RESPTYPE:
				if (b == MSG_CHAR_ACK) {
					printf("[ACK]");

					if (buffer[1] > 3) {
						state = RX_STATE_DATA;
						i = 0;
					}
					else {
						state = RX_STATE_CHECKSUM;
					}
				}
				else if (b == MSG_CHAR_NAK) {
					printf("[NAK]");
					state = RX_STATE_ERRCODE;
				}
				break;

			case RX_STATE_DATA:
				printf("%c", b);
				i++;

				if (i == buffer[1] - 2) {
					state = RX_STATE_CHECKSUM;
				}
				break;

			case RX_STATE_ERRCODE:
				printf("[E]");
				printf("[0x%02X]", b);

				state = RX_STATE_CHECKSUM;
				break;

			case RX_STATE_CHECKSUM:
				printf("[C]");
				printf("[0x%02X]", b);

				state = RX_STATE_END;
				break;

			case RX_STATE_END:
				printf("[N]");
				printf("[0x%02X]", b);

				if (b == MSG_CHAR_END) {
					printf("\n");
				}

				state = RX_STATE_START;
				break;
		}
	}
}

void processResponse(uint8_t * response, int responseLength)
{
	char				szResponse[80];
	char 				szTemperature[20];
	char 				szPressure[20];
	char 				szHumidity[20];
	static int			avgCount = 0;
	static bool			avgSave = true;
	static bool			minSave = false;
	static bool			maxSave = false;

	CurrentTime 		time;

	WebConnector & web = WebConnector::getInstance();

	QueueMgr & qmgr = QueueMgr::getInstance();
	RxFrame * pFrame = new RxFrame(response, responseLength);

#ifdef LOG_RXTX
	printFrame(response, responseLength);
#endif

	if (pFrame->isACK()) {
		switch (pFrame->getResponseCode()) {
			case RX_RSP_AVG_TPH:
				memcpy(szResponse, pFrame->getData(), pFrame->getDataLength());

				delete pFrame;

				strcpy(szTemperature, strtok(szResponse, ";"));
				strcpy(szPressure, strtok(NULL, ";"));
				strcpy(szHumidity, strtok(NULL, ";"));

				try {
					web.postAvgTPH(avgSave, &szTemperature[2], &szPressure[2], &szHumidity[2]);
					avgCount++;

					/*
					* Save every 20 minutes...
					*/
					if (avgCount < (AVG_MSGS_PER_MIN * 20)) {
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
					printf("Values: %s, \"AVG\", %s, %s, %s\n", time.getTimeStamp(), &szTemperature[2], &szPressure[2], &szHumidity[2]);

					vector<string> avgRecord = {time.getTimeStamp(), "AVG", &szTemperature[2], &szPressure[2], &szHumidity[2]};

					CSVHelper & csvAvg = CSVHelper::getInstance();

					csvAvg.writeRecord(5, avgRecord);
				}
				break;

			case RX_RSP_MAX_TPH:
				memcpy(szResponse, pFrame->getData(), pFrame->getDataLength());

				delete pFrame;

				strcpy(szTemperature, strtok(szResponse, ";"));
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

					vector<string> maxRecord = {time.getTimeStamp(), "MAX", &szTemperature[2], &szPressure[2], &szHumidity[2]};

					CSVHelper & csvMax = CSVHelper::getInstance();

					csvMax.writeRecord(5, maxRecord);
				}
				break;

			case RX_RSP_MIN_TPH:
				memcpy(szResponse, pFrame->getData(), pFrame->getDataLength());

				delete pFrame;

				strcpy(szTemperature, strtok(szResponse, ";"));
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

					vector<string> minRecord = {time.getTimeStamp(), "MIN", &szTemperature[2], &szPressure[2], &szHumidity[2]};

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

			case RX_RSP_WDT_DISABLE:
				break;

			case RX_RSP_GET_SCHED_VERSION:
				memcpy(szResponse, pFrame->getData(), pFrame->getDataLength());
				szResponse[pFrame->getDataLength() + 1] = 0;
				cout << "Scheduler version [" << szResponse << "]" << endl;

				qmgr.pushRx(pFrame);
				break;

			case RX_RSP_PING:
				break;
		}
	}
	else {
		printf("NAK received with error code [0x%02X]\n", pFrame->getErrorCode());
		delete pFrame;
	}
}
