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
#include "currenttime.h"

//#define LOG_RXTX

using namespace std;

queue<PFRAME>		txQueue;
SerialPort *		port;

pthread_mutex_t 	txLock;

pthread_t			tidTxCmd;

void * txCmdThread(void * pArgs)
{
	PFRAME				pTxFrame;
	uint32_t			txCount = 0;
	uint32_t			txAvgTPH = 0;
	uint32_t			txMinTPH = 1;
	uint32_t			txMaxTPH = 2;
	uint32_t			txResetMinMax;
	bool				go = true;
	uint8_t				data[MAX_REQUEST_MESSAGE_LENGTH];
	int					dataLength = 0;
	int					writeLen;
	int					bytesRead;

	SerialPort * 		port = (SerialPort *)pArgs;

	CurrentTime & 		time = CurrentTime::getInstance();

	/*
	** Calculate seconds to midnight...
	*/
	txResetMinMax = ((23 - time.getHour()) * 3600) + ((59 - time.getMinute()) * 60) + (59 - time.getMinute());

	cout << "Seconds till midnight: " << txResetMinMax << endl;

	while (go) {
		if (txCount == txAvgTPH) {
			/*
			** Next TX packet is a request for TPH data...
			*/
			data[0] = MSG_CHAR_START;
			data[1] = 2;
			data[2] = getMsgID();
			data[3] = RX_CMD_AVG_TPH;
			data[4] = 0x00FF - ((data[2] + data[3]) & 0x00FF);
			data[5] = MSG_CHAR_END;

			dataLength = 6;

			/*
			** Schedule next tx in 20 seconds...
			*/
			txAvgTPH = txCount + 20;
		}
		else if (txCount == txMinTPH) {
			/*
			** Next TX packet is a request for TPH data...
			*/
			data[0] = MSG_CHAR_START;
			data[1] = 2;
			data[2] = getMsgID();
			data[3] = RX_CMD_MIN_TPH;
			data[4] = 0x00FF - ((data[2] + data[3]) & 0x00FF);
			data[5] = MSG_CHAR_END;

			dataLength = 6;

			/*
			** Schedule next tx in 20 seconds...
			*/
			txMinTPH = txCount + 20;
		}
		else if (txCount == txMaxTPH) {
			/*
			** Next TX packet is a request for TPH data...
			*/
			data[0] = MSG_CHAR_START;
			data[1] = 2;
			data[2] = getMsgID();
			data[3] = RX_CMD_MAX_TPH;
			data[4] = 0x00FF - ((data[2] + data[3]) & 0x00FF);
			data[5] = MSG_CHAR_END;

			dataLength = 6;

			/*
			** Schedule next tx in 20 seconds...
			*/
			txMaxTPH = txCount + 20;
		}
		else if (txCount == txResetMinMax) {
			/*
			** Next TX packet is a request to reset min & max values...
			*/
			data[0] = MSG_CHAR_START;
			data[1] = 2;
			data[2] = getMsgID();
			data[3] = RX_CMD_RESET_MINMAX_TPH;
			data[4] = 0x00FF - ((data[2] + data[3]) & 0x00FF);
			data[5] = MSG_CHAR_END;

			dataLength = 6;

			/*
			** Schedule next tx in 24 hours...
			*/
			txResetMinMax = txCount + 86400;
		}
		else {
			pthread_mutex_lock(&txLock);

			/*
			** If there is something in the queue, send it next...
			*/
			if (!txQueue.empty()) {
				pTxFrame = txQueue.front();
				txQueue.pop();
				pthread_mutex_unlock(&txLock);

				memcpy(data, pTxFrame->data, pTxFrame->dataLength);

				dataLength = pTxFrame->dataLength;

				FrameManager & fm = FrameManager::getInstance();
				fm.freeFrame(pTxFrame);
			}
			else {
				pthread_mutex_unlock(&txLock);

				/*
				** Default is to send a ping...
				*/
				data[0] = MSG_CHAR_START;
				data[1] = 2;
				data[2] = getMsgID();
				data[3] = RX_CMD_PING;
				data[4] = 0x00FF - ((data[2] + data[3]) & 0x00FF);
				data[5] = MSG_CHAR_END;

				dataLength = 6;
			}
		}

#ifdef LOG_RXTX
		int i;
		printf("About to send[%d]: ", dataLength);
		for (i = 0;i < dataLength;i++) {
			printf("[0x%02X]", data[i]);
		}
		printf("\n");
#endif

		/*
		** Send cmd frame...
		*/
		try {
			writeLen = port->send(data, dataLength);
		}
		catch (Exception * e) {
			cout << "Error writing to port: " << e->getMessage() << endl;
			continue;
		}

#ifdef LOG_RXTX
		printf("TX[%d]: ", writeLen);
		for (i = 0;i < writeLen;i++) {
			printf("[0x%02X]", data[i]);
		}
		printf("\n");
#endif

		/*
		** Sleep for 100ms to give the Arduino
		** time to respond...
		*/
		usleep(100000L);

		/*
		** Read response frame...
		*/
		try {
			bytesRead = port->receive(data, MAX_REQUEST_MESSAGE_LENGTH);
		}
		catch (Exception * e) {
			cout << "Error reading port: " << e->getMessage() << endl;
			continue;
		}

		/*
		** Process response...
		*/
		if (bytesRead) {
#ifdef LOG_RXTX
			printf("RX[%d]: ", bytesRead);
#endif
			processResponse(data, bytesRead);
		}

		txCount++;

		/*
		** Sleep for 900 ms...
		*/
		usleep(900000L);
	}

	return NULL;
}

void cleanup(void)
{
	pthread_kill(tidTxCmd, SIGKILL);

	pthread_mutex_destroy(&txLock);

    delete port;
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
	char			szCommandBuffer[33];
	char			szCommand[32];
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
	 * Open the serial port...
	 */
	try {
		port = new SerialPort(szPort, SerialPort::mapBaudRate(atoi(szBaud)));
	}
	catch (Exception * e) {
		cout << "Failed to open serial port " << e->getMessage() << endl;
		return -1;
	}

	err = pthread_mutex_init(&txLock, NULL);

	if (err != 0) {
		printf("\nCan't create Tx mutex :[%s]", strerror(err));
		return -1;
	}

	/**************************************************************************
	** Create threads...
	**************************************************************************/

	/*
	 * Start cmd thread...
	 */
	err = pthread_create(&tidTxCmd, NULL, &txCmdThread, port);

	if (err != 0) {
		printf("ERROR! Can't create txCmdThread() :[%s]\n", strerror(err));
		return -1;
	}
	else {
		printf("Thread txCmdThread() created successfully\n");
	}

	while (1) {
		fgets(szCommandBuffer, sizeof(szCommand), stdin);

		i = 0;
		while (szCommandBuffer[i] != '\n') {
			szCommand[i] = szCommandBuffer[i];
			i++;
		}

		szCommand[i] = 0;
		
		if (strncmp(szCommand, "disable-wd-reset", sizeof(szCommand)) == 0) {
			FrameManager & frameMgr = FrameManager::getInstance();

			PFRAME pFrame = frameMgr.allocFrame();

			pFrame->data[0] = MSG_CHAR_START;
			pFrame->data[1] = 2;
			pFrame->data[2] = getMsgID();
			pFrame->data[3] = RX_CMD_WDT_DISABLE;
			pFrame->data[4] = 0x00FF - ((pFrame->data[2] + pFrame->data[3]) & 0x00FF);
			pFrame->data[5] = MSG_CHAR_END;

			pFrame->dataLength = 6;

			txQueue.push(pFrame);
		}

		usleep(1000L);
	}

	printf("Cleaning up and exiting!\n");
	
	cleanup();

	return 0;
}
