#ifndef BAUD
#define BAUD		57600
#endif

#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>

#include "sched/scheduler.h"
#include "rtc_atmega328p.h"
#include "taskdef.h"
#include "rxtxmsgdef.h"
#include "serial_atmega328p.h"

#define MSG_STORE_SIZE				4


uint8_t			txBuffer[64];
uint8_t			txLength = 0;

RXMSGSTRUCT		rxMsgStore[MSG_STORE_SIZE];

void setupSerial()
{
	memset(rxMsgStore, 0, sizeof(RXMSGSTRUCT) * MSG_STORE_SIZE);

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

PRXMSGSTRUCT allocateRxMsgStruct()
{
	PRXMSGSTRUCT	m = NULL;
	int				i = 0;

	for (i = 0;i < MSG_STORE_SIZE;i++) {
		if (!rxMsgStore[i].isAllocated) {
			m = &rxMsgStore[i];
			m->isAllocated = 1;
			break;
		}
	}

	return m;
}

void freeRxMsgStruct(PRXMSGSTRUCT m)
{
	m->isAllocated = 0;
}

/*
** Rx Complete Interrupt Handler
*/
ISR(USART_RX_vect, ISR_BLOCK)
{
	static uint8_t		state = RX_STATE_START;
	static uint8_t		i = 0;
	static PRXMSGSTRUCT	pMsgStruct = NULL;

	uint8_t	b = UDR0;

	switch (state) {
		case RX_STATE_START:
			/*
			 * Allocate the msg structure for this message...
			 */
			pMsgStruct = allocateRxMsgStruct();

			pMsgStruct->frame.start = b;
			state = RX_STATE_LENGTH;
			break;

		case RX_STATE_LENGTH:
			pMsgStruct->frame.cmdFrameLength = b;

			if (pMsgStruct->frame.cmdFrameLength > MAX_CMD_FRAME_LENGTH) {
				pMsgStruct->frame.cmdFrameLength = MAX_CMD_FRAME_LENGTH;
				pMsgStruct->rxErrorCode = MSG_NAK_DATA_OVERRUN;
			}
			state = RX_STATE_MSGID;
			break;

		case RX_STATE_MSGID:
			pMsgStruct->frame.msgID = b;
			state = RX_STATE_CMD;
			break;

		case RX_STATE_CMD:
			pMsgStruct->frame.cmd = b;
			state = RX_STATE_DATA;
			break;

		case RX_STATE_DATA:
			pMsgStruct->frame.data[i++] = b;

			if (i == (pMsgStruct->frame.cmdFrameLength - 2)) {
				state = RX_STATE_CHECKSUM;
				i = 0;
			}
			break;

		case RX_STATE_CHECKSUM:
			pMsgStruct->frame.checksum = b;
			state = RX_STATE_END;
			break;

		case RX_STATE_END:
			if (b == MSG_CHAR_END) {
				state = RX_STATE_START;
			}
			else {
				pMsgStruct->rxErrorCode = MSG_NAK_DATA_OVERRUN;
			}

			scheduleTask(TASK_RXCMD, rtc_val_ms(2), pMsgStruct);
			break;
	}
}
