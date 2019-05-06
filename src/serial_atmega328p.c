#ifndef BAUD
#define BAUD		57600
#endif

#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#include "sched/scheduler.h"
#include "taskdef.h"
#include "rxtxmsgdef.h"
#include "serial_atmega328p.h"

uint8_t			txBuffer[64];
uint8_t			txLength = 0;

void setupSerial()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

#if USE_2X
	UCSR0A |= _BV(U2X0);
#else
	UCSR0A &= ~(_BV(U2X0));
#endif

	/*
	** Set data byte size to 8-bit, 1 stop bit
	*/
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00) | _BV(USBS0);
	
	/*
	** Enable Tx
	** Enable Tx interrupts
	*/
	UCSR0B = _BV(TXEN0) | _BV(TXCIE0);
}

void enableTxInterrupt()
{
	/*
	** Enable the data register empty interrupt...
	*/
	UCSR0B |= _BV(UDRIE0);
}

void disableTxInterrupt()
{
	/*
	** Mask the data register empty interrupt...
	*/
	UCSR0B &= ~_BV(UDRIE0);
}

uint8_t getNextTxByte(uint8_t isInit)
{
	static uint8_t		i = 0;
	uint8_t				rtn;
	
	if (isInit) {
		i = 0;
	}
	
	if (i < txLength) {
		rtn = txBuffer[i];
		i++;
	}
	else {
		rtn = 0;
		disableTxInterrupt();
	}
	
	return rtn;
}

void txstr(char * pszData, uint8_t dataLength)
{
	int			i;
	
	if (dataLength > 64) {
		dataLength = 64;
	}
	
	for (i = 0;i < dataLength;i++) {
		txBuffer[i] = pszData[i];
	}
	
	txLength = dataLength;
	
	UDR0 = getNextTxByte(1);
	
	enableTxInterrupt();
}

/*
** Rx Complete Interrupt Handler
*/
ISR(USART_RX_vect, ISR_BLOCK)
{
	static RXMSGSTRUCT	msgStruct;

	static uint8_t		state = RX_STATE_START;
	static uint8_t		i = 0;

	uint8_t	b = UDR0;

	switch (state) {
		case RX_STATE_START:
			msgStruct.frame.start = b;
			state = RX_STATE_LENGTH;
			break;

		case RX_STATE_LENGTH:
			msgStruct.frame.cmdFrameLength = b;

			if (msgStruct.frame.cmdFrameLength > MAX_CMD_FRAME_LENGTH) {
				msgStruct.frame.cmdFrameLength = MAX_CMD_FRAME_LENGTH;
				msgStruct.rxErrorCode = MSG_NAK_DATA_OVERRUN;
			}
			state = RX_STATE_MSGID;
			break;

		case RX_STATE_MSGID:
			msgStruct.frame.msgID = b;
			state = RX_STATE_CMD;
			break;

		case RX_STATE_CMD:
			msgStruct.frame.cmd = b;
			state = RX_STATE_DATA;
			break;

		case RX_STATE_DATA:
			msgStruct.frame.data[i++] = b;

			if (i == (msgStruct.frame.cmdFrameLength - 2)) {
				state = RX_STATE_CHECKSUM;
				i = 0;
			}
			break;

		case RX_STATE_CHECKSUM:
			msgStruct.frame.checksum = b;
			state = RX_STATE_END;
			break;

		case RX_STATE_END:
			if (b == MSG_CHAR_END) {
				state = RX_STATE_START;
			}
			else {
				msgStruct.rxErrorCode = MSG_NAK_DATA_OVERRUN;
			}

			scheduleTask(TASK_RXCMD, 10, &msgStruct);
			break;
	}
}

/*
** Tx Complete (Data Register Empty) Interrupt Handler
*/
ISR(USART_UDRE_vect, ISR_BLOCK)
{
	uint8_t		b;
	
	b = getNextTxByte(0);
	
	if (b != 0) {
		UDR0 = b;
	}
}
