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
#include <sys/time.h>
#include <sys/types.h>

#include "serial.h"
#include "exception.h"
#include "avrweather.h"

SerialPort::SerialPort()
{	
}

SerialPort::~SerialPort()
{
	/*
	 * Set the old port parameters...
	 */
	if ((tcsetattr(fd, TCSANOW, &old_settings)) != 0) {
        printf("Error setting old attributes\n");
	}

	closePort();
}

void SerialPort::openPort(char * pszPort, int baudRate, bool isBlocking)
{
	char				szExceptionText[1024];
	int					flags;

	flags = O_RDWR | O_NOCTTY | O_NDELAY;

	if (!isBlocking) {
		flags |= O_NONBLOCK;
	}

	/*
	 * Open the serial port...
	 */
	fd = open(pszPort, flags);

	if (fd < 0) {
		sprintf(szExceptionText, "Error opening %s: %s", pszPort, strerror(errno));
        throw new Exception(szExceptionText);
    }

	/*
	** Set read timeout...
	*/
	tv.tv_sec = 3;
	tv.tv_usec = 0;

	/*
	 * Get current port parameters...
	 */
	tcgetattr(fd, &new_settings);

	old_settings = new_settings;

	new_settings.c_iflag = IGNBRK;
	new_settings.c_oflag = 0;
	new_settings.c_lflag = 0;
	new_settings.c_cflag = (CS8 | CREAD | CLOCAL);

	new_settings.c_cc[VMIN]  = 6;							// Read minimum 6 characters
	new_settings.c_cc[VTIME] = 0;  							// 3 sec wait...

	/*
	 * Set the baud rate...
	 */
	cfsetispeed(&new_settings, baudRate);
	cfsetospeed(&new_settings, baudRate);

	/*
	 * Set the new port parameters...
	 */
	if ((tcsetattr(fd, TCSANOW, &new_settings)) != 0) {
		close(fd);
        throw new Exception("Error setting attributes");
	}

	if (!isBlocking) {
		int rc;
		rc = fcntl(fd, F_GETFL, 0);

		if (rc != -1) {
			fcntl(fd, F_SETFL, rc & ~O_NONBLOCK);
		}
	}
}

void SerialPort::closePort()
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
	int		bytesRead = 0;
	int		rc;

	FD_ZERO(&fdSet);
	FD_SET(fd, &fdSet);

	rc = select(fd + 1, &fdSet, NULL, NULL, &tv);

	if (rc == -1) {
		throw new Exception("Error calling select()");
	}
	else if (rc == 0) {
		printf("Read timeout occurred...");
	}
	else {
		bytesRead = read(fd, pBuffer, requestedBytes);
	}

	FD_ZERO(&fdSet);
	FD_SET(fd, &fdSet);

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
