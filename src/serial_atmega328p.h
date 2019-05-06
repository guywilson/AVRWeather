#include <stdint.h>

#ifndef _INCL_SERIAL_ATMEGA328P
#define _INCL_SERIAL_ATMEGA328P

/*
** Request frame (6 - 80 bytes)
** <START><LENGTH><MSG_ID><CMD><DATA (0 - 74)><CHECKSUM><END>
**                 |                        |
**                  --included in checksum--
**
** ACK response frame
** <START><LENGTH><MSG_ID><ACK><DATA><CHECKSUM><END>
**
** NAK response frame
** <START><MSG_ID><NAK><ERR_CODE><END>
*/

#define NUM_REQUEST_FRAME_BYTES		  6
#define MAX_DATA_LENGTH				 74
#define MAX_REQUEST_MESSAGE_LENGTH	(NUM_FRAME_BYTES + MAX_DATA_LENGTH)

#define MAX_CMD_FRAME_LENGTH		 76		// Data + msgID + cmd

#define MSG_CHAR_START				0x7E
#define MSG_CHAR_END				0x81

#define MSG_CHAR_ACK				0x06
#define MSG_CHAR_NAK				0x15

#define MSG_NAK_UNKNOWN_CMD			0x01
#define MSG_NAK_INVALID_CHECKSUM	0x02
#define MSG_NAK_DATA_ERROR			0x04
#define MSG_NAK_DATA_OVERRUN		0x08

#define RX_STATE_START				0x01
#define RX_STATE_LENGTH				0x02
#define RX_STATE_MSGID				0x03
#define RX_STATE_CMD				0x04
#define RX_STATE_DATA				0x05
#define RX_STATE_CHECKSUM			0x06
#define RX_STATE_END				0x07

#define RX_CMD_TPH					0x01
#define RX_CMD_ANEMOMETER			0x02
#define RX_CMD_RAINGUAGE			0x04


typedef struct {
	uint8_t			start;
	uint8_t			cmdFrameLength;
	uint8_t			msgID;
	uint8_t			cmd;

	uint8_t			data[MAX_DATA_LENGTH];

	uint8_t			checksum;
	uint8_t			end;
}
RXMSGFRAME;

typedef RXMSGFRAME *	PRXMSGFRAME;

typedef struct {
	RXMSGFRAME		frame;

	uint8_t			rxErrorCode;
	uint8_t			isAllocated;
}
RXMSGSTRUCT;

typedef RXMSGSTRUCT *	PRXMSGSTRUCT;


void setupSerial();

void enableTxInterrupt();
void disableTxInterrupt();

void txstr(char * pszData, uint8_t dataLength);

PRXMSGSTRUCT allocateRxMsgStruct();
void freeRxMsgStruct(PRXMSGSTRUCT m);

#endif
