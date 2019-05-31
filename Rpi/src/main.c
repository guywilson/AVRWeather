#include <stdint.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#include "rxtxmsgdef.h"

#ifndef SERIAL_PORT
#define SERIAL_PORT			"/dev/tty.usbmodem14101"
#endif

int openSerialPort(char * pszPort, int speed)
{
	int				fd;
	int				rc;
	struct termios 	t;

	/*
	 * Open the serial port...
	 */
	fd = open(pszPort, O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (fd < 0) {
        printf("Error opening %s: %s\n", pszPort, strerror(errno));
        return -1;
    }

	/*
	 * Get current port parameters...
	 */
	tcgetattr(fd, &t);

	t.c_iflag = IGNBRK;
	t.c_oflag = 0;
	t.c_lflag = 0;
	t.c_cflag = (CS8 | CREAD | CLOCAL);

//	t.c_cflag &= ~PARENB;   					/* Disables the Parity Enable bit(PARENB),So No Parity   */
//	t.c_cflag &= ~CSTOPB;   					/* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
//	t.c_cflag &= ~CSIZE;	 					/* Clears the mask for setting the data size             */
//	t.c_cflag |=  CS8;      					/* Set the data bits = 8                                 */
//
//	t.c_cflag &= ~CRTSCTS;       				/* No Hardware flow Control                         	 */
//	t.c_cflag |= CREAD | CLOCAL; 				/* Enable receiver,Ignore Modem Control lines            */
//
//
//	t.c_iflag &= ~(IXON | IXOFF | IXANY);		/* Disable XON/XOFF flow control both i/p and o/p        */
//	t.c_iflag &= ~(ICANON|ECHO|ECHOE|ISIG);		/* Non Cannonical mode                                   */
//
//	t.c_oflag &= ~OPOST;						/* No Output Processing                                  */
	
	t.c_cc[VMIN]  = 6;							/* Read minimum 6 characters                             */
	t.c_cc[VTIME] = 0;  						/* No wait                                               */

	/*
	 * Set the baud rate...
	 */
	cfsetispeed(&t, speed);
	cfsetospeed(&t, speed);
	
	/*
	 * Set the new port parameters...
	 */
	if ((tcsetattr(fd, TCSANOW, &t)) != 0) {
		printf("\n  ERROR ! in Setting attributes\n");
		close(fd);
		return -1;
	}

	/*
	 * Set blocking read...
	 */
	rc = fcntl(fd, F_GETFL, 0);

	if (rc != -1) {
		fcntl(fd, F_SETFL, rc & ~O_NONBLOCK);
	}

	return fd;
}

int processByte(uint8_t b)
{
	static int 			state = RX_STATE_START;
	static int			i;
	static RXMSGFRAME	frame;

	int 				rtn = 1;

	switch (state) {
		case RX_STATE_START:
			printf("[S]");
			printf("[0x%02X]", b);
			if (b == MSG_CHAR_START) {
				frame.start = b;
				state = RX_STATE_LENGTH;
			}
			break;

		case RX_STATE_LENGTH:
			printf("[L]");
			printf("[%d]", b);
			frame.frameLength = b;
			state = RX_STATE_MSGID;
			break;

		case RX_STATE_MSGID:
			printf("[M]");
			printf("[0x%02X]", b);
			frame.msgID = b;
			state = RX_STATE_RESPTYPE;
			break;

		case RX_STATE_RESPTYPE:
			if (b == MSG_CHAR_ACK) {
				printf("[ACK]");
				frame.responseType = MSG_CHAR_ACK;

				if (frame.frameLength > 2) {
					state = RX_STATE_DATA;
					i = 0;
				}
				else {
					state = RX_STATE_CHECKSUM;
				}
			}
			else if (b == MSG_CHAR_NAK) {
				printf("[NAK]");
				frame.responseType = MSG_CHAR_NAK;

				state = RX_STATE_ERRCODE;
			}
			break;

		case RX_STATE_DATA:
			printf("%c", b);
			frame.data[i++] = b;

			if (i == frame.frameLength - 2) {
				state = RX_STATE_CHECKSUM;
			}
			break;

		case RX_STATE_ERRCODE:
			printf("[E]");
			printf("[0x%02X]", b);
			frame.errorCode = b;
			state = RX_STATE_CHECKSUM;
			break;

		case RX_STATE_CHECKSUM:
			printf("[C]");
			printf("[0x%02X]", b);
			frame.checksum = b;
			state = RX_STATE_END;
			break;

		case RX_STATE_END:
			printf("[N]");
			printf("[0x%02X]", b);
			if (b == MSG_CHAR_END) {
				frame.end = b;
				rtn = 0;
			}

			state = RX_STATE_START;
			break;
	}

	return rtn;
}

void * queryTPHThread(void * pArgs)
{
	uint8_t		msgID = 1;
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
			for (i = 0;i < bytesRead;i++) {
				processByte(frame[i]);
			}
		}
		else if (bytesRead < 0) {
			if (errno) {
				printf("E[%s]", strerror(errno));
			}
		}

		printf("\n");

		sleep(5);
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	int			err;
	pthread_t	tid;
	char		szPort[128];
	int			fd;

	if (argc > 1) {
		strcpy(szPort, &argv[1][0]);
	}
	else {
		strcpy(szPort, SERIAL_PORT);
	}

	fd = openSerialPort(szPort, B115200);

	if (fd < 0) {
		return -1;
	}

	err = pthread_create(&tid, NULL, &queryTPHThread, &fd);

    if (err != 0) {
    	printf("\nCan't create thread :[%s]", strerror(err));
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
