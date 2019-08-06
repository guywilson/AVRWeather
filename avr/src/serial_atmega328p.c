#ifndef BAUD
#define BAUD		9600
#endif

#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/setbaud.h>
#include <scheduler.h>
#include <schederr.h>

#include "rtc_atmega328p.h"
#include "taskdef.h"
#include "rxtxmsgdef.h"
#include "serial_atmega328p.h"

#define enableTxInterrupt()			UCSR0B |= _BV(UDRIE0)
#define disableTxInterrupt()		UCSR0B &= ~_BV(UDRIE0)


uint8_t			txBuffer[80];
uint8_t			txLength = 0;

uint8_t 		ackFrame[80];

uint8_t 		nakFrame[NUM_NAK_RSP_FRAME_BYTES] = {
	MSG_CHAR_START,
	0x00,				// Length
	0x00,				// Message ID
	0x00,				// Response code
	MSG_CHAR_NAK,
	0x00,				// NAK error code
	0x00,				// Checksum
	MSG_CHAR_END
};

RXMSGSTRUCT		msgStruct;
PRXMSGSTRUCT	pMsgStruct = &msgStruct;

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
	** Enable Tx & Rx
	** Enable Tx & Rx interrupts
	*/
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(TXCIE0);
}

int getNextTxByte(uint8_t isInit)
{
	static uint8_t		i = 0;
	int					rtn;
	
	if (isInit) {
		i = 0;
	}

	if (i == txLength) {
		disableTxInterrupt();
		rtn = -1;
	}
	else {
		rtn = (int)txBuffer[i++];
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

uint8_t * getNakFrame(uint8_t messageID, uint8_t responseCode, uint8_t nakCode)
{
	uint16_t		checksum = 0;

	nakFrame[1] = 4;
	nakFrame[2] = messageID;
	nakFrame[3] = responseCode;
	nakFrame[5] = nakCode;

	checksum = nakFrame[2] + nakFrame[3] + nakFrame[4] + nakFrame[5];

	nakFrame[6] = (uint8_t)(0x00FF - (checksum & 0x00FF));

	return nakFrame;
}

void txNAK(uint8_t messageID, uint8_t responseCode, uint8_t nakCode)
{
	uint8_t	*	pNakFrame;

	pNakFrame = getNakFrame(messageID, responseCode, nakCode);

	txmsg(pNakFrame, NUM_NAK_RSP_FRAME_BYTES);
}

void txACK(uint8_t messageID, uint8_t responseCode, char * pData, int dataLength)
{
	int				i = 0;
	uint16_t		checksum = 0;

	memset(ackFrame, 0, 80);

	ackFrame[0] = MSG_CHAR_START;
	ackFrame[1] = (uint8_t)((dataLength + 3) & 0x00FF);
	ackFrame[2] = messageID;
	ackFrame[3] = responseCode;
	ackFrame[4] = MSG_CHAR_ACK;

	checksum = ackFrame[2] + ackFrame[3] + ackFrame[4];

	if (dataLength > 0) {
		for (i = 0;i < dataLength;i++) {
			ackFrame[i + 5] = pData[i];
			checksum += pData[i];
		}
	}

	ackFrame[i + 5] = (uint8_t)(0x00FF - (checksum & 0x00FF));
	ackFrame[i + 6] = MSG_CHAR_END;

	txmsg(ackFrame, dataLength + NUM_ACK_RSP_FRAME_BYTES);
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

	switch (state) {
		case RX_STATE_START:
			if (b == MSG_CHAR_START) {
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
			pMsgStruct->frameChecksumTotal = b;
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
				pMsgStruct->rxErrorCode = b;
			}

			state = RX_STATE_START;

			scheduleTask(TASK_RXCMD, rtc_val_ms(10), pMsgStruct);
			break;
	}
}

/*
** Tx Complete (Data Register Empty) Interrupt Handler
*/
void handleDRE()
{
	int b;

	b = getNextTxByte(0);

	if (b != -1) {
		UDR0 = (uint8_t)b;
	}
}
