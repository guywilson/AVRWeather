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

char		szBuffer[80];

void RxTask(PTASKPARM p)
{
	PRXMSGSTRUCT	pMsgStruct;
	int				valueLen = 0;
	int				i = 0;

	pMsgStruct = (PRXMSGSTRUCT)p;

	if (pMsgStruct->rxErrorCode != 0) {
		txNAK(pMsgStruct->frame.msgID, pMsgStruct->rxErrorCode);
	}
	else {
		switch (pMsgStruct->frame.cmd) {
			case RX_CMD_TPH:
				szBuffer[i++] = 'T';
				szBuffer[i++] = ':';

				valueLen = getTemperature(&szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'P';
				szBuffer[i++] = ':';

				valueLen = getPressure(&szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'H';
				szBuffer[i++] = ':';

				valueLen = getHumidity(&szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				txACK(pMsgStruct->frame.msgID, szBuffer, i);
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
}

void TxTask(PTASKPARM p)
{
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
