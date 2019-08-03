#include <termios.h>

#ifndef _INCL_SERIAL
#define _INCL_SERIAL

class SerialPort
{
public:
    static SerialPort & getInstance() {
        static SerialPort instance;
        return instance;
    }

private:
	int					fd;
	fd_set				fdSet;
	struct timeval		tv;

	struct termios		new_settings;
	struct termios		old_settings;

	SerialPort();

public:
						~SerialPort();

	void 				openPort(char * pszPort, int baudRate, bool isBlocking);
	void				closePort();

	static int 			mapBaudRate(int speed);

	int					send(uint8_t * pBuffer, int writeLength);
	int					receive(uint8_t * pBuffer, int requestedBytes);
};

#endif
