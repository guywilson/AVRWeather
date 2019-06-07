#include <iostream>
#include <cstring>
#include <string>
#include <queue>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "serial.h"
#include "exception.h"
#include "avrweather.h"

using namespace std;

#define FRAME_MEM_SIZE				10


FRAME				_frameMem[FRAME_MEM_SIZE];

queue<PFRAME>		txQueue;
queue<PFRAME>		rxQueue;
pthread_mutex_t 	txLock;
pthread_mutex_t 	rxLock;

FRAME * allocFrame()
{
	PFRAME 		frame = NULL;
	int			i;

	for (i = 0;i < FRAME_MEM_SIZE;i++) {
		if (!_frameMem[i].isAllocated) {
			frame = &_frameMem[i];
			frame->isAllocated = 1;
			break;
		}
	}

	return frame;
}

void freeFrame(PFRAME frame)
{
	memset(frame, 0, sizeof(FRAME));
}

void * txrxDeamon(void * pArgs)
{
	int				go = 1;
	int				i;
	int				writeLen;
	int				bytesRead = 0;

	PFRAME			pTxFrame;
	PFRAME			pRxFrame;
	SerialPort * 	port;

	port = (SerialPort *)pArgs;

	while (go) {
		while (txQueue.empty()) {
			usleep(1000L);
		}

		pthread_mutex_lock(&txLock);

		pTxFrame = txQueue.front();

		pthread_mutex_unlock(&txLock);

		/*
		 * Write cmd frame...
		 */
		try {
			writeLen = port->send(pTxFrame->data, pTxFrame->dataLength);
		}
		catch (Exception * e) {
			cout << "Error writing to port: " << e->getMessage() << endl;
			continue;
		}

		printf("TX[%d]: ", writeLen);
		for (i = 0;i < writeLen;i++) {
			printf("[0x%02X]", pTxFrame->data[i]);
		}
		printf("\n");

		freeFrame(pTxFrame);

		pRxFrame = allocFrame();

		if (pRxFrame == NULL) {
			cout << "ERROR: Cannot allocate frame buffer" << endl;
			continue;
		}

		usleep(100000L);

		/*
		 * Read response frame...
		 */
		try {
			bytesRead = port->receive(pRxFrame->data, MAX_REQUEST_MESSAGE_LENGTH);
		}
		catch (Exception * e) {
			cout << "Error reading port: " << e->getMessage() << endl;
			continue;
		}

		printf("RX[%d]: ", bytesRead);
		for (i = 0;i < bytesRead;i++) {
			printf("[0x%02X]", pRxFrame->data[i]);
		}
		printf("\n");

		pthread_mutex_lock(&rxLock);

		rxQueue.push(pRxFrame);

		pthread_mutex_unlock(&rxLock);
	}

	return NULL;
}

void * queryTPHThread(void * pArgs)
{
	PFRAME			pTxFrame;
	PFRAME			pRxFrame;
	PRXMSGSTRUCT	pMsg;
	RXMSGSTRUCT		msg;
	uint8_t			msgID = 0x00;
	int				go = 1;
	char			szTPH[80];
	char 			szTemperature[20];
	char 			szPressure[20];
	char 			szHumidity[20];
	FILE *			fptr;
	struct tm *		time;

	fptr = fopen("./data.csv", "at");

	if (fptr == NULL) {
		printf("Failed to open CSV file");
		return NULL;
	}

	fprintf(fptr, "TIME,TEMPERATURE,PRESSURE,HUMIDITY\n");

	pMsg = &msg;

	while (go) {
		pTxFrame = allocFrame();

		pTxFrame->data[0] = MSG_CHAR_START;
		pTxFrame->data[1] = 2;
		pTxFrame->data[2] = msgID++;
		pTxFrame->data[3] = RX_CMD_TPH;
		pTxFrame->data[4] = 0x00FF - ((pTxFrame->data[2] + pTxFrame->data[3]) & 0x00FF);
		pTxFrame->data[5] = MSG_CHAR_END;

		pTxFrame->dataLength = 6;

		/*
		 * Write cmd frame...
		 */
		pthread_mutex_lock(&txLock);

		txQueue.push(pTxFrame);

		pthread_mutex_unlock(&txLock);

		/*
		 * Read response frame...
		 */
		while (rxQueue.empty()) {
			usleep(1000L);
		}

		pthread_mutex_lock(&rxLock);

		pRxFrame = rxQueue.front();

		pthread_mutex_unlock(&rxLock);

		printf("RX[%d]: ", pRxFrame->dataLength);

		if (pRxFrame->dataLength > 0) {
			processFrame(pMsg, pRxFrame->data, pRxFrame->dataLength);

			time = localtime(&pMsg->timeStamp);

			memcpy(szTPH, pMsg->frame.data, pMsg->frame.frameLength - 2);

			strcpy(szTemperature, strtok(szTPH, ";"));
			strcpy(szPressure, strtok(NULL, ";"));
			strcpy(szHumidity, strtok(NULL, ";"));

			fprintf(
				fptr,
				"%d-%02d-%02d %02d:%02d:%02d,%s,%s,%s\n",
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
		}

		printf("\n");

		sleep(2);
	}

	fclose(fptr);

	return NULL;
}

int main(int argc, char *argv[])
{
	int				err;
	pthread_t		tid;
	SerialPort *	port;
	char			szPort[128];
	char			szBaud[8];
	int				i;

	if (argc > 1) {
		for (i = 1;i < argc;i++) {
			if (argv[i][0] == '-') {
				if (strcmp(&argv[i][1], "port") == 0) {
					strcpy(szPort, &argv[++i][0]);
				}
				else if (strcmp(&argv[i][1], "baud") == 0) {
					strcpy(szBaud, &argv[++i][0]);
				}
			}
		}
	}
	else {
		printf("Usage:\n");
		printf("\twctl -port [serialPort] -baud [baudrate]\n\n");
		return -1;
	}

	/*
	 * Open the serial port...
	 */
	port = new SerialPort(szPort, SerialPort::mapBaudRate(atoi(szBaud)));

	err = pthread_mutex_init(&txLock, NULL);

	if (err != 0) {
		printf("\nCan't create Tx mutex :[%s]", strerror(err));
		return -1;
	}

	err = pthread_mutex_init(&rxLock, NULL);

	if (err != 0) {
		printf("\nCan't create Rx mutex :[%s]", strerror(err));
		return -1;
	}

	err = pthread_create(&tid, NULL, &txrxDeamon, port);

	if (err != 0) {
		printf("\nCan't create txrxDeamon thread :[%s]", strerror(err));
		return -1;
	}
	else {
		printf("\nThread txrxDeamon created successfully\n");
	}

	err = pthread_create(&tid, NULL, &queryTPHThread, NULL);

	if (err != 0) {
		printf("\nCan't create queryTPHThread thread :[%s]", strerror(err));
		return -1;
	}
	else {
		printf("\nThread queryTPHThread created successfully\n");
	}

    while (1) {
    	usleep(1000L);
    }

	pthread_mutex_destroy(&rxLock);
	pthread_mutex_destroy(&txLock);

    delete port;

	return 0;
}
