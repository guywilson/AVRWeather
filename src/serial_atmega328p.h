#include <stdint.h>

#ifndef _INCL_SERIAL_ATMEGA328P
#define _INCL_SERIAL_ATMEGA328P

void setupSerial();

void enableTxInterrupt();
void disableTxInterrupt();

void txstr(char * pszData, uint8_t dataLength);

#endif