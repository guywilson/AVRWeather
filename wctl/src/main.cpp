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
#include "queuemgr.h"
#include "avrweather.h"
#include "currenttime.h"
#include "mongoose.h"
#include "webconnect.h"

//#define LOG_RXTX
//#define WEB_LISTENER_TEST

using namespace std;

SerialPort *		port;
pthread_t			tidTxCmd;

static void avrCommandHandler(struct mg_connection * connection, int event, void * p)
{
	struct http_message *			message;
	char *							pszMethod;
	char *							pszURI;
	char							szCmdValue[32];
	int								rtn;
	uint8_t							cmdCode;
	bool							isSerialCommand = false;

	switch (event) {
		case MG_EV_HTTP_REQUEST:
			message = (struct http_message *)p;

			pszMethod = (char *)malloc(message->method.len + 1);

			if (pszMethod == NULL) {
				throw new Exception("Failed to allocate memory for method...");
			}

			memcpy(pszMethod, message->method.p, message->method.len);
			pszMethod[message->method.len] = 0;

			pszURI = (char *)malloc(message->uri.len + 1);

			if (pszURI == NULL) {
				throw new Exception("Failed to allocate memory for URI...");
			}

			memcpy(pszURI, message->uri.p, message->uri.len);
			pszURI[message->uri.len] = 0;

			cout << "Got " << pszMethod << " request for '" << pszURI << "'" << endl;

			if (strncmp(pszMethod, "GET", 4) == 0) {
				rtn = mg_get_http_var(&message->query_string, "command", szCmdValue, 32);

				if (rtn < 0) {
					throw new Exception("Failed to find form variable 'command'");
				}

				cout << "Got command: " << szCmdValue << endl;

				if (strncmp(szCmdValue, "disable-wd-reset", sizeof(szCmdValue)) == 0) {
					cmdCode = RX_CMD_WDT_DISABLE;
					isSerialCommand = true;
				}
				else if (strncmp(szCmdValue, "reset-min-max", sizeof(szCmdValue)) == 0) {
					cmdCode = RX_CMD_RESET_MINMAX_TPH;
					isSerialCommand = true;
				}
				else if (strncmp(szCmdValue, "get-scheduler-version", sizeof(szCmdValue)) == 0) {
					cmdCode = RX_CMD_GET_SCHED_VERSION;
					isSerialCommand = true;
				}
				else if (strncmp(szCmdValue, "reset-avr", sizeof(szCmdValue)) == 0) {
					resetAVR();
					isSerialCommand = false;
				}
				else {
					cmdCode = RX_CMD_PING;
					isSerialCommand = true;
				}

				if (isSerialCommand) {
					QueueMgr & qmgr = QueueMgr::getInstance();

					TxFrame * pFrame = new TxFrame(NULL, 0, cmdCode);

					qmgr.pushTx(pFrame);
				}
			}

			free(pszMethod);
			free(pszURI);

			mg_printf(connection, "HTTP/1.0 200 OK");
			connection->flags |= MG_F_SEND_AND_CLOSE;
			break;

		default:
			break;
	}
}

static void avrViewHandler(struct mg_connection * connection, int event, void * p)
{
	struct http_message *			message;
	char *							pszMethod;
	char *							pszURI;

	switch (event) {
		case MG_EV_HTTP_REQUEST:
			message = (struct http_message *)p;

			pszMethod = (char *)malloc(message->method.len + 1);

			if (pszMethod == NULL) {
				throw new Exception("Failed to allocate memory for method...");
			}

			memcpy(pszMethod, message->method.p, message->method.len);
			pszMethod[message->method.len] = 0;

			pszURI = (char *)malloc(message->uri.len + 1);

			if (pszURI == NULL) {
				throw new Exception("Failed to allocate memory for URI...");
			}

			memcpy(pszURI, message->uri.p, message->uri.len);
			pszURI[message->uri.len] = 0;

			cout << "Got " << pszMethod << " request for '" << pszURI << "'" << endl;
	
			if (strncmp(pszMethod, "GET", 3) == 0) {
				struct mg_serve_http_opts opts = { .document_root = "./resources/html" };

				cout << "Serving file '" << pszURI << "'" << endl;

				mg_serve_http(connection, message, opts);
			}

			free(pszMethod);
			free(pszURI);

			mg_printf(connection, "HTTP/1.0 200 OK");
			connection->flags |= MG_F_SEND_AND_CLOSE;
			break;

		default:
			break;
	}
}

static void cssHandler(struct mg_connection * connection, int event, void * p)
{
	struct http_message *			message;
	char *							pszMethod;
	char *							pszURI;

	switch (event) {
		case MG_EV_HTTP_REQUEST:
			message = (struct http_message *)p;

			pszMethod = (char *)malloc(message->method.len + 1);

			if (pszMethod == NULL) {
				throw new Exception("Failed to allocate memory for method...");
			}

			memcpy(pszMethod, message->method.p, message->method.len);
			pszMethod[message->method.len] = 0;

			pszURI = (char *)malloc(message->uri.len + 1);

			if (pszURI == NULL) {
				throw new Exception("Failed to allocate memory for URI...");
			}

			memcpy(pszURI, message->uri.p, message->uri.len);
			pszURI[message->uri.len] = 0;

			cout << "Got " << pszMethod << " request for '" << pszURI << "'" << endl;

			if (strncmp(pszMethod, "GET", 3) == 0) {
				struct mg_serve_http_opts opts = { .document_root = "./resources" };

				cout << "Serving file '" << pszURI << "'" << endl;

				mg_serve_http(connection, message, opts);
			}

			free(pszMethod);
			free(pszURI);

			mg_printf(connection, "HTTP/1.0 200 OK");
			connection->flags |= MG_F_SEND_AND_CLOSE;
			break;

		default:
			break;
	}
}

void * txCmdThread(void * pArgs)
{
	TxFrame *			pTxFrame;
	uint32_t			txCount = 0;
	uint32_t			txAvgTPH = 0;
	uint32_t			txMinTPH = 1;
	uint32_t			txMaxTPH = 2;
	uint32_t			txResetMinMax;
	bool				go = true;
	uint8_t				data[MAX_REQUEST_MESSAGE_LENGTH];
	int					writeLen;
	int					bytesRead;

	SerialPort * 		port = (SerialPort *)pArgs;

	CurrentTime 		time;

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
			pTxFrame = new TxFrame(NULL, 0, RX_CMD_AVG_TPH);

			/*
			** Schedule next tx in 20 seconds...
			*/
			txAvgTPH = txCount + 20;
		}
		else if (txCount == txMinTPH) {
			/*
			** Next TX packet is a request for TPH data...
			*/
			pTxFrame = new TxFrame(NULL, 0, RX_CMD_MIN_TPH);

			/*
			** Schedule next tx in 20 seconds...
			*/
			txMinTPH = txCount + 20;
		}
		else if (txCount == txMaxTPH) {
			/*
			** Next TX packet is a request for TPH data...
			*/
			pTxFrame = new TxFrame(NULL, 0, RX_CMD_MAX_TPH);

			/*
			** Schedule next tx in 20 seconds...
			*/
			txMaxTPH = txCount + 20;
		}
		else if (txCount == txResetMinMax) {
			/*
			** Next TX packet is a request to reset min & max values...
			*/
			pTxFrame = new TxFrame(NULL, 0, RX_CMD_RESET_MINMAX_TPH);

			/*
			** Schedule next tx in 24 hours...
			*/
			txResetMinMax = txCount + 86400;
		}
		else {
			/*
			** If there is something in the queue, send it next...
			*/
			QueueMgr & qmgr = QueueMgr::getInstance();

			if (!qmgr.isTxQueueEmpty()) {
				pTxFrame = qmgr.popTx();
			}
			else {
				/*
				** Default is to send a ping...
				*/
				pTxFrame = new TxFrame(NULL, 0, RX_CMD_PING);
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
			writeLen = port->send(pTxFrame->getFrame(), pTxFrame->getFrameLength());
		}
		catch (Exception * e) {
			cout << "Error writing to port: " << e->getMessage() << endl;
			continue;
		}

		delete pTxFrame;

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
#ifndef WEB_LISTENER_TEST
	pthread_kill(tidTxCmd, SIGKILL);

    delete port;
#endif
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
	 * Open the serial port...
	 */
#ifndef WEB_LISTENER_TEST
	try {
		port = new SerialPort(szPort, SerialPort::mapBaudRate(atoi(szBaud)));
	}
	catch (Exception * e) {
		cout << "Failed to open serial port " << e->getMessage() << endl;
		return -1;
	}

	/**************************************************************************
	** Create threads...
	**************************************************************************/

	int				err;

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
#endif

	WebConnector & web = WebConnector::getInstance();

	web.registerHandler("/avr/cmd", avrViewHandler);
	web.registerHandler("/avr/cmd/post", avrCommandHandler);
	web.registerHandler("/css", cssHandler);

	web.listen();

	cout << "Cleaning up and exiting!" << endl;
	
	cleanup();

	return 0;
}
