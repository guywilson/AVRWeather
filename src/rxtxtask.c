#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "sched/scheduler.h"
#include "serial_atmega328p.h"
#include "taskdef.h"
#include "adctask.h"
#include "anemometer.h"
#include "rainguage.h"
#include "rxtxtask.h"

uint8_t ackFrame[80];

void txNAK(uint8_t messageID, uint8_t nakCode)
{
	uint8_t	*	pNakFrame;

	pNakFrame = getNakFrame(messageID, nakCode);

	txmsg(pNakFrame, 5);
}

void txACK(uint8_t messageID, uint8_t * pData, uint8_t dataLength)
{
	int				i;
	uint16_t		checksum = 0;

	memset(ackFrame, 0, 80);

	ackFrame[0] = MSG_CHAR_START;
	ackFrame[1] = dataLength + 2;
	ackFrame[2] = messageID;
	ackFrame[3] = MSG_CHAR_ACK;

	checksum = ackFrame[2] + ackFrame[3];

	for (i = 0;i < dataLength;i++) {
		ackFrame[i + 4] = pData[i];
		checksum += pData[i];
	}

	ackFrame[i] = (uint8_t)(0x00FF - (checksum & 0x00FF));
	ackFrame[i + 1] = MSG_CHAR_END;

	txmsg(ackFrame, dataLength + 6);
}

void RxTask(PTASKPARM p)
{
	PRXMSGSTRUCT	pMsgStruct;
	char			szData[48];
	int				valueLen = 0;
	int				i = 0;

	pMsgStruct = (PRXMSGSTRUCT)p;

	if (pMsgStruct->rxErrorCode != 0) {
		txNAK(pMsgStruct->frame.msgID, pMsgStruct->rxErrorCode);
	}
	else {
		switch (pMsgStruct->frame.cmd) {
			case RX_CMD_TPH:
				szData[i++] = 'T';
				szData[i++] = ':';

				valueLen = getTemperature(&szData[i]);

				i += valueLen;

				szData[i++] = ';';

				szData[i++] = 'P';
				szData[i++] = ':';

				valueLen = getPressure(&szData[i]);

				i += valueLen;

				szData[i++] = ';';

				szData[i++] = 'H';
				szData[i++] = ':';

				valueLen = getHumidity(&szData[i]);

				i += valueLen;

				szData[i++] = ';';

				szData[i] = 0;

				txACK(pMsgStruct->frame.msgID, (uint8_t *)szData, strlen(szData));
				break;

			case RX_CMD_ANEMOMETER:
				break;

			case RX_CMD_RAINGUAGE:
				break;

			default:
				txNAK(pMsgStruct->frame.msgID, MSG_NAK_UNKNOWN_CMD);
				break;
		}
	}

	freeRxMsgStruct(pMsgStruct);
}

void TxTask(PTASKPARM p)
{
	char		szBuffer[64];
	uint8_t		len;
	int			i = 0;

	szBuffer[i++] = '<';
	szBuffer[i++] = 't';
	szBuffer[i++] = ':';
	len = getTemperature(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'p';
	szBuffer[i++] = ':';
	len = getPressure(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'h';
	szBuffer[i++] = ':';
	len = getHumidity(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'w';
	szBuffer[i++] = ':';
	len = getMaxWindSpeed(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'r';
	szBuffer[i++] = ':';
	len = getRainfall(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;

	szBuffer[i++] = '\n';
	szBuffer[i] = 0;

	txstr(szBuffer, i);
	
	rescheduleTask(TASK_TX, NULL);
}
