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

#define FRAME_MEM_SIZE				16

using namespace std;

FrameManager *		fm;

queue<PFRAME>		txQueue;
pthread_mutex_t 	txLock;

FILE *				fptrCSV;

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
		pthread_mutex_lock(&txLock);

		if (!txQueue.empty()) {
			pTxFrame = txQueue.front();
			txQueue.pop();
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

			fm->freeFrame(pTxFrame);

			pRxFrame = fm->allocFrame();

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

			/*
			 * Process response...
			 */
			printf("RX[%d]: ", bytesRead);
			if (bytesRead) {
				processResponse(fptrCSV, pRxFrame->data, bytesRead);
			}

			fm->freeFrame(pRxFrame);
		}
		else {
			pthread_mutex_unlock(&txLock);
		}

		usleep(1000L);
	}

	return NULL;
}

void * queryTPHThread(void * pArgs)
{
	PFRAME			pTxFrame;
	int				go = 1;

	while (go) {
		pTxFrame = fm->allocFrame();

		if (pTxFrame == NULL) {
			printf("Error allocating frame\n");
			break;
		}

		pTxFrame->data[0] = MSG_CHAR_START;
		pTxFrame->data[1] = 2;
		pTxFrame->data[2] = getMsgID();
		pTxFrame->data[3] = RX_CMD_TPH;
		pTxFrame->data[4] = 0x00FF - ((pTxFrame->data[2] + pTxFrame->data[3]) & 0x00FF);
		pTxFrame->data[5] = MSG_CHAR_END;

		pTxFrame->dataLength = 6;

		/*
		 * Send TPH frame...
		 */
		pthread_mutex_lock(&txLock);
		txQueue.push(pTxFrame);
		pthread_mutex_unlock(&txLock);

		sleep(20);
	}

	return NULL;
}

void * pingThread(void * pArgs)
{
	PFRAME			pTxFrame;
	int				go = 1;

	while (go) {
		pTxFrame = fm->allocFrame();

		if (pTxFrame == NULL) {
			printf("Error allocating frame\n");
			break;
		}

		pTxFrame->data[0] = MSG_CHAR_START;
		pTxFrame->data[1] = 2;
		pTxFrame->data[2] = getMsgID();
		pTxFrame->data[3] = RX_CMD_PING;
		pTxFrame->data[4] = 0x00FF - ((pTxFrame->data[2] + pTxFrame->data[3]) & 0x00FF);
		pTxFrame->data[5] = MSG_CHAR_END;

		pTxFrame->dataLength = 6;

		/*
		 * Send TPH frame...
		 */
		pthread_mutex_lock(&txLock);
		txQueue.push(pTxFrame);
		pthread_mutex_unlock(&txLock);

		sleep(1);
	}

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
	 * Allocate frame memory...
	 */
	try {
		fm = new FrameManager(FRAME_MEM_SIZE);
	}
	catch(Exception * e) {
		cout << "Failed to initialise frame memory " << e->getMessage() << endl;
		return -1;
	}

	/*
	 * Open the serial port...
	 */
	try {
		port = new SerialPort(szPort, SerialPort::mapBaudRate(atoi(szBaud)));
	}
	catch (Exception * e) {
		cout << "Failed to open serial port " << e->getMessage() << endl;
		return -1;
	}

	/*
	 * Open the CSV file...
	 */
	fptrCSV = fopen("./data.csv", "at");

	if (fptrCSV == NULL) {
		printf("Failed to open CSV file");
		return -1;
	}

	fprintf(fptrCSV, "TIME,TEMPERATURE,PRESSURE,HUMIDITY\n");

	err = pthread_mutex_init(&txLock, NULL);

	if (err != 0) {
		printf("\nCan't create Tx mutex :[%s]", strerror(err));
		return -1;
	}

	err = pthread_create(&tid, NULL, &pingThread, NULL);

	if (err != 0) {
		printf("\nCan't create pingThread thread :[%s]", strerror(err));
		return -1;
	}
	else {
		printf("\nThread pingThread created successfully\n");
	}

	err = pthread_create(&tid, NULL, &queryTPHThread, NULL);

	if (err != 0) {
		printf("\nCan't create queryTPHThread thread :[%s]", strerror(err));
		return -1;
	}
	else {
		printf("\nThread queryTPHThread created successfully\n");
	}

	err = pthread_create(&tid, NULL, &txrxDeamon, port);

	if (err != 0) {
		printf("\nCan't create txrxDeamon thread :[%s]", strerror(err));
		return -1;
	}
	else {
		printf("\nThread txrxDeamon created successfully\n");
	}

    while (1) {
    	usleep(1000L);
    }

	pthread_mutex_destroy(&txLock);

	fclose(fptrCSV);

    delete port;
    delete fm;

	return 0;
}
