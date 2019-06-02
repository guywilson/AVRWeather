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
#include "exception.h"

SerialPort::SerialPort(char * pszPort, int baudRate)
{
	int			rc;
	char		szExceptionText[1024];

	/*
	 * Open the serial port...
	 */
	fd = open(pszPort, O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (fd < 0) {
		sprintf(szExceptionText, "Error opening %s: %s", pszPort, strerror(errno));
        throw new Exception(szExceptionText);
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
	cfsetispeed(&t, baudRate);
	cfsetospeed(&t, baudRate);

	/*
	 * Set the new port parameters...
	 */
	if ((tcsetattr(fd, TCSANOW, &t)) != 0) {
		close(fd);

		sprintf(szExceptionText, "Error setting attributes");
        throw new Exception(szExceptionText);
	}

	/*
	 * Set blocking read...
	 */
	rc = fcntl(fd, F_GETFL, 0);

	if (rc != -1) {
		fcntl(fd, F_SETFL, rc & ~O_NONBLOCK);
	}
}

SerialPort::~SerialPort()
{
	close(fd);
}

int SerialPort::send(uint8_t * pBuffer, int writeLength)
{
	int		bytesWritten;

	bytesWritten = write(fd, pBuffer, writeLength);

	if (bytesWritten < 0) {
		throw new Exception("Error writing to port");
	}

	return bytesWritten;
}

int SerialPort::receive(uint8_t * pBuffer, int requestedBytes)
{
	char	szExceptionText[256];
	int		bytesRead;
	int		errCount = 0;

	bytesRead = read(fd, pBuffer, requestedBytes);

	while (bytesRead < 0 && errCount < 10) {
		bytesRead = read(fd, pBuffer, requestedBytes);

		if (bytesRead < 0) {
			errCount++;
		}

		usleep(100000L);
	}

	if (errCount) {
		sprintf(szExceptionText, "Error reading from port: %s", strerror(errno));
        throw new Exception(szExceptionText);
	}

	return bytesRead;
}

int SerialPort::mapBaudRate(int baud)
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
