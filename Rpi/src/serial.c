#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "serial.h"

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

int processFrame(uint8_t * buffer, int bufferLength)
{
	static int 			state = RX_STATE_START;
	static int			i;
	static RXMSGFRAME	frame;

	int					count = 0;
	int 				rtn = 1;
	uint8_t				b;

	while (count < bufferLength) {
		b = buffer[count++];

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
	}

	return rtn;
}

int mapBaudRate(int baud)
{
	int		baudConst = B9600;

	switch (baud) {
		case 50:
			baudConst = B50;
			break;

		case 75:
			baudConst = B75;
			break;

		case 110:
			baudConst = B110;
			break;

		case 134:
			baudConst = B134;
			break;

		case 150:
			baudConst = B150;
			break;

		case 200:
			baudConst = B200;
			break;

		case 300:
			baudConst = B300;
			break;

		case 600:
			baudConst = B600;
			break;

		case 1200:
			baudConst = B1200;
			break;

		case 1800:
			baudConst = B1800;
			break;

		case 2400:
			baudConst = B2400;
			break;

		case 4800:
			baudConst = B4800;
			break;

		case 9600:
			baudConst = B9600;
			break;

		case 19200:
			baudConst = B19200;
			break;

		case 38400:
			baudConst = B38400;
			break;

		case 57600:
			baudConst = B57600;
			break;

		case 115200:
			baudConst = B115200;
			break;

		case 230400:
			baudConst = B230400;
			break;

		default:
			printf("Unsupported baud rate [%d], supported rates are 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400\n", baud);
			printf("Defaulting to 9600 baud\n");
			break;
	}

	return baudConst;
}
