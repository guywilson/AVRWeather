#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "serial.h"

void * queryTPHThread(void * pArgs)
{
	uint8_t		msgID = 0x00;
	int			go = 1;
	int			frameLength = 0;
	int			writeLen;
	int			bytesRead = 0;
	int			i;
	int			errCount = 0;
	uint8_t		frame[80];
	int	*		fd;

	fd = (int *)pArgs;

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
			processFrame(frame, bytesRead);
		}
		else if (bytesRead < 0) {
			if (errno) {
				printf("E[%s]", strerror(errno));
			}
		}

		printf("\n");

		sleep(2);
	}

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
