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
#include <signal.h>

#include "serial.h"
#include "exception.h"
#include "avrweather.h"

#define FRAME_MEM_SIZE				16
//#define LOG_RXTX

using namespace std;

FrameManager *		fm;
queue<PFRAME>		txQueue;
pthread_mutex_t 	txLock;
SerialPort *		port;
FILE *				fptrCSV;

pthread_t			tidPing;
pthread_t			tidAvgTPH;
pthread_t			tidMinMaxTPH;


void * queryAvgTPHThread(void * pArgs)
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
		pTxFrame->data[3] = RX_CMD_AVG_TPH;
		pTxFrame->data[4] = 0x00FF - ((pTxFrame->data[2] + pTxFrame->data[3]) & 0x00FF);
		pTxFrame->data[5] = MSG_CHAR_END;

		pTxFrame->dataLength = 6;

		/*
		 * Send TPH frame...
		 */
		pthread_mutex_lock(&txLock);
		txQueue.push(pTxFrame);
		pthread_mutex_unlock(&txLock);

		/*
		 * Sleep for 20 seconds...
		 */
		sleep(20);
	}

	return NULL;
}

void * queryMinMaxTPHThread(void * pArgs)
{
	PFRAME			pTxFrame;
	int				go = 1;
	time_t			t;
	struct tm *		tm;

	t = time(0);
	tm = localtime(&t);

	while (go) {
		while (!(tm->tm_hour == 23 && tm->tm_min == 59 && tm->tm_sec >= 57)) {
			t = time(0);
			tm = localtime(&t);

			sleep(2);
		}

		/*
		 * Get MIN TPH for the last period...
		 */
		pTxFrame = fm->allocFrame();

		if (pTxFrame == NULL) {
			printf("Error allocating frame\n");
			break;
		}

		pTxFrame->data[0] = MSG_CHAR_START;
		pTxFrame->data[1] = 2;
		pTxFrame->data[2] = getMsgID();
		pTxFrame->data[3] = RX_CMD_MIN_TPH;
		pTxFrame->data[4] = 0x00FF - ((pTxFrame->data[2] + pTxFrame->data[3]) & 0x00FF);
		pTxFrame->data[5] = MSG_CHAR_END;

		pTxFrame->dataLength = 6;

		pthread_mutex_lock(&txLock);
		txQueue.push(pTxFrame);
		pthread_mutex_unlock(&txLock);

		sleep(1);

		/*
		 * Get MAX TPH for the last period...
		 */
		pTxFrame = fm->allocFrame();

		if (pTxFrame == NULL) {
			printf("Error allocating frame\n");
			break;
		}

		pTxFrame->data[0] = MSG_CHAR_START;
		pTxFrame->data[1] = 2;
		pTxFrame->data[2] = getMsgID();
		pTxFrame->data[3] = RX_CMD_MAX_TPH;
		pTxFrame->data[4] = 0x00FF - ((pTxFrame->data[2] + pTxFrame->data[3]) & 0x00FF);
		pTxFrame->data[5] = MSG_CHAR_END;

		pTxFrame->dataLength = 6;

		pthread_mutex_lock(&txLock);
		txQueue.push(pTxFrame);
		pthread_mutex_unlock(&txLock);

		sleep(1);

		/*
		 * Reset MIN & MAX TPH...
		 */
		pTxFrame = fm->allocFrame();

		if (pTxFrame == NULL) {
			printf("Error allocating frame\n");
			break;
		}

		pTxFrame->data[0] = MSG_CHAR_START;
		pTxFrame->data[1] = 2;
		pTxFrame->data[2] = getMsgID();
		pTxFrame->data[3] = RX_CMD_RESET_MINMAX_TPH;
		pTxFrame->data[4] = 0x00FF - ((pTxFrame->data[2] + pTxFrame->data[3]) & 0x00FF);
		pTxFrame->data[5] = MSG_CHAR_END;

		pTxFrame->dataLength = 6;

		pthread_mutex_lock(&txLock);
		txQueue.push(pTxFrame);
		pthread_mutex_unlock(&txLock);

		/*
		 * Sleep for 20 hours...
		 */
		sleep(72000);
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
		 * Send ping frame...
		 */
		pthread_mutex_lock(&txLock);
		txQueue.push(pTxFrame);
		pthread_mutex_unlock(&txLock);

		sleep(1);
	}

	return NULL;
}

void txrxDeamon(SerialPort * port)
{
	int				go = 1;
	int				writeLen;
	int				bytesRead = 0;

	PFRAME			pTxFrame;
	PFRAME			pRxFrame;

#ifdef LOG_RXTX
	int				i;
#endif

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
#ifdef LOG_RXTX
			for (i = 0;i < writeLen;i++) {
				printf("[0x%02X]", pTxFrame->data[i]);
			}
#endif
			printf("\n");

			fm->freeFrame(pTxFrame);

			usleep(100000L);

			pRxFrame = fm->allocFrame();

			if (pRxFrame == NULL) {
				cout << "ERROR: Cannot allocate frame buffer" << endl;
				continue;
			}

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
}

void cleanup(void)
{
	/*
	 * Kill threads...
	 */
	pthread_kill(tidPing, SIGKILL);
	pthread_kill(tidAvgTPH, SIGKILL);
	pthread_kill(tidMinMaxTPH, SIGKILL);

	pthread_mutex_destroy(&txLock);

	fclose(fptrCSV);

    delete port;
    delete fm;
}

void handleSignal(int sigNum)
{
	switch (sigNum) {
		case SIGINT:
			printf("Detected SIGINT, cleaning up...\n");
			break;

		case SIGTERM:
			printf("Detected SIGTERM, cleaning up...\n");
			break;
	}

	cleanup();

    exit(0);
}

int main(int argc, char *argv[])
{
	int				err;
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
	 * Register signal handler for cleanup...
	 */
	if (signal(SIGINT, &handleSignal) == SIG_ERR) {
		printf("Failed to register signal handler for SIGINT\n");
		return -1;
	}

	if (signal(SIGTERM, &handleSignal) == SIG_ERR) {
		printf("Failed to register signal handler for SIGTERM\n");
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
	fptrCSV = fopen("./tph.csv", "at");

	if (fptrCSV == NULL) {
		printf("Failed to open CSV file");
		return -1;
	}

	fprintf(fptrCSV, "TIME,TYPE,TEMPERATURE,PRESSURE,HUMIDITY\n");

	err = pthread_mutex_init(&txLock, NULL);

	if (err != 0) {
		printf("\nCan't create Tx mutex :[%s]", strerror(err));
		return -1;
	}

	/**************************************************************************
	** Create threads...
	**************************************************************************/

	/*
	 * Ping every second...
	 */
	err = pthread_create(&tidPing, NULL, &pingThread, NULL);

	if (err != 0) {
		printf("ERROR! Can't create pingThread thread :[%s]\n", strerror(err));
		return -1;
	}
	else {
		printf("Thread pingThread() created successfully\n");
	}

	/*
	 * Get average temperature, pressure & humidity every 20 seconds...
	 */
	err = pthread_create(&tidAvgTPH, NULL, &queryAvgTPHThread, NULL);

	if (err != 0) {
		printf("ERROR! Can't create queryAvgTPHThread thread :[%s]\n", strerror(err));
		return -1;
	}
	else {
		printf("Thread queryAvgTPHThread() created successfully\n");
	}

	/*
	 * Get minimum & maximum TPH just before midnight...
	 */
	err = pthread_create(&tidMinMaxTPH, NULL, &queryMinMaxTPHThread, NULL);

	if (err != 0) {
		printf("ERROR! Can't create queryMinMaxTPHThread thread :[%s]\n", strerror(err));
		return -1;
	}
	else {
		printf("Thread queryMinMaxTPHThread() created successfully\n");
	}

	/*
	 * This function actually sends the queued commands over the
	 * serial port.
	 *
	 * NOTE: This must be set up last as it never returns...
	 */
	txrxDeamon(port);

	cleanup();

	return 0;
}
