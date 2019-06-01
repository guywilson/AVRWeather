#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "serial.h"

void * queryTPHThread(void * pArgs)
{
	PRXMSGSTRUCT	pMsg;
	RXMSGSTRUCT		msg;
	uint8_t			msgID = 0x00;
	int				go = 1;
	int				frameLength = 0;
	int				writeLen;
	int				bytesRead = 0;
	int				i;
	int				errCount = 0;
	int				rtn;
	uint8_t			frame[80];
	char			szTPH[80];
	char 			szTemperature[20];
	char 			szPressure[20];
	char 			szHumidity[20];
	FILE *			fptr;
	struct tm *		time;
	int	*			fd;

	fd = (int *)pArgs;

	fptr = fopen("./data.csv", "at");

	if (fptr == NULL) {
		printf("Failed to open CSV file");
		return NULL;
	}

	fprintf(fptr, "TIME,TEMPERATURE,PRESSURE,HUMIDITY\n");

	pMsg = &msg;

	while (go) {
		frame[0] = MSG_CHAR_START;
		frame[1] = 2;
		frame[2] = msgID++;
		frame[3] = RX_CMD_TPH;
		frame[4] = 0x00FF - ((frame[2] + frame[3]) & 0x00FF);
		frame[5] = MSG_CHAR_END;

		frameLength = 6;

		/*
		 * Write cmd frame...
		 */
		writeLen = write(*fd, frame, frameLength);

		printf("TX[%d]: ", writeLen);
		for (i = 0;i < writeLen;i++) {
			printf("[0x%02X]", frame[i]);
		}
		printf("\n");

		/*
		 * Clear frame...
		 */
		memset(frame, 0, 80);

		/*
		 * Wait 50ms for response...
		 */
		usleep(50000L);

		errCount = 0;

		/*
		 * Read response frame...
		 */
		bytesRead = read(*fd, frame, 80);

		while (bytesRead < 0 && errCount < 10) {
			bytesRead = read(*fd, frame, 80);
			usleep(100000L);
			errCount++;
		}

		printf("RX[%d]: ", bytesRead);

		if (bytesRead > 0) {
			memset(&msg, 0, sizeof(msg));

			rtn = processFrame(pMsg, frame, bytesRead);

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
		else if (bytesRead < 0) {
			if (errno) {
				printf("E[%s]", strerror(errno));
			}
		}

		printf("\n");

		sleep(2);
	}

	fclose(fptr);

	return NULL;
}

int main(int argc, char *argv[])
{
	int			err;
	pthread_t	tid;
	char		szPort[128];
	char		szBaud[8];
	int			baud;
	int			fd;
	int			i;

	if (argc > 1) {
		for (i = 1;i < argc;i++) {
			if (argv[i][0] == '-') {
				if (strcmp(&argv[i][1], "port") == 0) {
					strcpy(szPort, &argv[++i][0]);
				}
				else if (strcmp(&argv[i][1], "baud") == 0) {
					strcpy(szBaud, &argv[++i][0]);
					baud = mapBaudRate(atoi(szBaud));
				}
			}
		}
	}
	else {
		printf("Usage:\n");
		printf("\twctl -port [serialPort] -baud [baudrate]\n\n");
		return -1;
	}

	fd = openSerialPort(szPort, baud);

	if (fd < 0) {
		return -1;
	}

	err = pthread_create(&tid, NULL, &queryTPHThread, &fd);

    if (err != 0) {
    	printf("\nCan't create thread :[%s]", strerror(err));
    	return -1;
    }
    else {
    	printf("\nThread created successfully\n");
    }

    while (1) {
    	usleep(1000L);
    }

	close(fd);

	return 0;
}
