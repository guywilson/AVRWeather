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
#include "sched/schederr.h"
#include "serial_atmega328p.h"

#define MSG_STORE_SIZE				4


uint8_t			txBuffer[64];
uint8_t			txLength = 0;

uint8_t nakFrame[5] = {
	MSG_CHAR_START,
	0x00,				// Message ID
	MSG_CHAR_NAK,
	0x00,				// NAK error code
	MSG_CHAR_END
};

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
	** Enable Tx & Rx
	** Enable Tx & Rx interrupts
	*/
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(TXCIE0);
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

void txmsg(uint8_t * pMsg, uint8_t dataLength)
{
	int			i;

	if (dataLength > MAX_REQUEST_MESSAGE_LENGTH) {
		dataLength = MAX_REQUEST_MESSAGE_LENGTH;
	}

	for (i = 0;i < dataLength;i++) {
		txBuffer[i] = pMsg[i];
	}

	txLength = dataLength;

	UDR0 = getNextTxByte(1);

	enableTxInterrupt();
}

uint8_t * getNakFrame(uint8_t messageID, uint8_t nakCode)
{
	nakFrame[1] = messageID;
	nakFrame[3] = nakCode;

	return nakFrame;
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
	memset(m, 0, sizeof(RXMSGSTRUCT));
}

/*
** Rx Complete Interrupt Handler
**
** This function uses a state machine to read the
** message byte by byte. The checksum is calculated
** as we receive each byte...
*/
void handleRxComplete(uint8_t b)
{
	static uint8_t		state = RX_STATE_START;
	static uint8_t		i = 0;
	static PRXMSGSTRUCT	pMsgStruct = NULL;

	switch (state) {
		case RX_STATE_START:
			if (b == MSG_CHAR_START) {
				/*
				 * Allocate the msg structure for this message...
				 */
				pMsgStruct = allocateRxMsgStruct();

				pMsgStruct->frame.start = b;
				state = RX_STATE_LENGTH;
			}
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
			pMsgStruct->frameChecksumTotal += b;
			state = RX_STATE_CMD;
			break;

		case RX_STATE_CMD:
			pMsgStruct->frame.cmd = b;
			pMsgStruct->frameChecksumTotal += b;

			if (pMsgStruct->frame.cmdFrameLength == 2) {
				state = RX_STATE_CHECKSUM;
			}
			else {
				state = RX_STATE_DATA;
				i = 0;
			}
			break;

		case RX_STATE_DATA:
			pMsgStruct->frame.data[i++] = b;
			pMsgStruct->frameChecksumTotal += b;

			if (i == (pMsgStruct->frame.cmdFrameLength - 2)) {
				state = RX_STATE_CHECKSUM;
				i = 0;
			}
			break;

		case RX_STATE_CHECKSUM:
			pMsgStruct->frame.checksum = b;
			pMsgStruct->frameChecksumTotal += b;

			/*
			 * Validate the checksum...
			 */
			if ((pMsgStruct->frameChecksumTotal & 0x00FF) != 0x00FF) {
				pMsgStruct->rxErrorCode = MSG_NAK_INVALID_CHECKSUM;
			}

			state = RX_STATE_END;
			break;

		case RX_STATE_END:
			if (b != MSG_CHAR_END) {
				pMsgStruct->rxErrorCode = MSG_NAK_DATA_OVERRUN;
			}

			state = RX_STATE_START;

			scheduleTask(TASK_RXCMD, rtc_val_ms(2), pMsgStruct);
			break;
	}
}

/*
** Tx Complete (Data Register Empty) Interrupt Handler
*/
void handleDRE()
{
	UDR0 = getNextTxByte(0);
}
