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
#include "logger.h"

//#define SERIAL_ENABLE_SELECT

static uint8_t emulated_cmd_buffer[MAX_REQUEST_MESSAGE_LENGTH];
static uint8_t emulated_rsp_buffer[MAX_RESPONSE_MESSAGE_LENGTH];

static int emulated_cmd_length = 0;
static int emulated_rsp_length = 0;

static void _build_response_frame(char * data, int dataLength)
{
	uint16_t			checksumTotal = 0;
	int					i;

	emulated_rsp_buffer[0] = MSG_CHAR_START;
	emulated_rsp_buffer[1] = (uint8_t)dataLength + 2;
	emulated_rsp_buffer[2] = emulated_cmd_buffer[2];
	emulated_rsp_buffer[3] = (emulated_cmd_buffer[3] << 4);
	emulated_rsp_buffer[4] = MSG_CHAR_ACK;
	
	checksumTotal = (emulated_rsp_buffer[2] + emulated_rsp_buffer[3]) + emulated_rsp_buffer[4];

	for (i = 0;i < dataLength;i++) {
		emulated_rsp_buffer[i + 5] = (uint8_t)data[i];

		checksumTotal += emulated_rsp_buffer[i + 5];
	}

	emulated_rsp_buffer[5 + dataLength] = (uint8_t)(0x00FF - (checksumTotal & 0x00FF));
	emulated_rsp_buffer[6 + dataLength] = MSG_CHAR_END;

	emulated_rsp_length = dataLength + NUM_ACK_RSP_FRAME_BYTES;
}

SerialPort::SerialPort()
{
	isEmulationMode = false;
}

SerialPort::~SerialPort()
{
	/*
	 * Set the old port parameters...
	 */
	if ((tcsetattr(fd, TCSANOW, &old_settings)) != 0) {
        log.logError("Error setting old attributes");
	}

	closePort();
}

void SerialPort::_openSerialPort(char * pszPort, int baudRate, bool isBlocking)
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
	tv.tv_sec = 0;
	tv.tv_usec = 200000;

	/*
	 * Get current port parameters...
	 */
	tcgetattr(fd, &new_settings);

	old_settings = new_settings;

	new_settings.c_iflag = IGNBRK;
	new_settings.c_oflag = 0;
	new_settings.c_lflag = 0;
	new_settings.c_cflag = (CS8 | CREAD | CLOCAL);

	new_settings.c_cc[VMIN]  = NUM_ACK_RSP_FRAME_BYTES;		// Read minimum 7 characters
	new_settings.c_cc[VTIME] = 0;  							// wait...

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

void SerialPort::openPort(char * pszPort, int baudRate, bool isBlocking)
{
	if (!isEmulationMode) {
		_openSerialPort(pszPort, baudRate, isBlocking);
	}
}

void SerialPort::closePort()
{
	close(fd);
}

void SerialPort::setEmulationMode()
{
	isEmulationMode = true;
}

int SerialPort::_send_serial(uint8_t * pBuffer, int writeLength)
{
	int		bytesWritten;

	bytesWritten = write(fd, pBuffer, writeLength);

	if (bytesWritten < 0) {
		throw new Exception("Error writing to port");
	}

	return bytesWritten;
}

int SerialPort::_receive_serial(uint8_t * pBuffer, int requestedBytes)
{
	int		bytesRead = 0;
#ifdef SERIAL_ENABLE_SELECT
	int		rc;

	FD_ZERO(&fdSet);
	FD_SET(fd, &fdSet);

	rc = select(fd + 1, &fdSet, NULL, NULL, &tv);

	if (rc == -1) {
		throw new Exception("Error calling select()");
	}
	else if (rc == 0) {
		log.logInfo("Read timeout occurred...");
	}
	else {
#endif
		bytesRead = read(fd, pBuffer, requestedBytes);
#ifdef SERIAL_ENABLE_SELECT
	}

	FD_ZERO(&fdSet);
	FD_SET(fd, &fdSet);
#endif

	return bytesRead;
}

int SerialPort::_send_emulated(uint8_t * pBuffer, int writeLength)
{
	int					bytesWritten;
	uint8_t				cmdCode = 0;
	int					dataLength;
	char *				data;
	static const char *	avgTPH = "T:25.28;P:1010.10;H:52.25;";
	static const char *	minTPH = "T:21.21;P:1007.13;H:49.17;";
	static const char *	maxTPH = "T:27.12;P:1012.23;H:57.74;";

	memset(emulated_cmd_buffer, 0, MAX_REQUEST_MESSAGE_LENGTH);
	memset(emulated_rsp_buffer, 0, MAX_RESPONSE_MESSAGE_LENGTH);

	memcpy(emulated_cmd_buffer, pBuffer, writeLength);

	emulated_cmd_length = writeLength;
	bytesWritten = writeLength;

	cmdCode = emulated_cmd_buffer[3];

	switch (cmdCode) {
		case RX_CMD_AVG_TPH:
			data = (char *)avgTPH;
			dataLength = strlen(data);

			_build_response_frame(data, dataLength);
			break;

		case RX_CMD_MAX_TPH:
			data = (char *)maxTPH;
			dataLength = strlen(data);

			_build_response_frame(data, dataLength);
			break;

		case RX_CMD_MIN_TPH:
			data = (char *)minTPH;
			dataLength = strlen(data);

			_build_response_frame(data, dataLength);
			break;

		case RX_CMD_PING:
			data = (char *)NULL;
			dataLength = 0;

			_build_response_frame(data, dataLength);
			break;

		case RX_CMD_GET_SCHED_VERSION:
			data = (char *)"1.2.01 2019-07-30 17:37:20";
			dataLength = strlen(data);

			_build_response_frame(data, dataLength);
			break;

		default:
			data = (char *)NULL;
			dataLength = 0;

			_build_response_frame(data, dataLength);
			break;
	}

	return bytesWritten;
}

int SerialPort::_receive_emulated(uint8_t * pBuffer, int requestedBytes)
{
	int		bytesRead = 0;
	
	usleep(100000L);

	bytesRead = emulated_rsp_length;

	memcpy(pBuffer, emulated_rsp_buffer, emulated_rsp_length);
	
	return bytesRead;
}

int SerialPort::send(uint8_t * pBuffer, int writeLength)
{
	if (isEmulationMode) {
		return _send_emulated(pBuffer, writeLength);
	}
	else {
		return _send_serial(pBuffer, writeLength);
	}
}

int SerialPort::receive(uint8_t * pBuffer, int requestedBytes)
{
	if (isEmulationMode) {
		return _receive_emulated(pBuffer, requestedBytes);
	}
	else {
		return _receive_serial(pBuffer, requestedBytes);
	}
}

int SerialPort::mapBaudRate(int baud)
{
	int			baudConst = B9600;
	Logger & 	log = Logger::getInstance();

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
			log.logError("Unsupported baud rate [%d], supported rates are 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400", baud);
			log.logInfo("Defaulting to 9600 baud");
			break;
	}

	return baudConst;
}
