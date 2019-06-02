#include <termios.h>

#ifndef _INCL_SERIAL
#define _INCL_SERIAL

class SerialPort
{
private:
	int					fd;
	struct termios		t;

public:
						SerialPort(char * pszPort, int baudRate);
						~SerialPort();

	static int 			mapBaudRate(int speed);

	int					send(uint8_t * pBuffer, int writeLength);
	int					receive(uint8_t * pBuffer, int requestedBytes);
};

#endif
