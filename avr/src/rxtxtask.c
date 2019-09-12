#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <scheduler.h>
#include "serial_atmega328p.h"
#include "taskdef.h"
#include "adctask.h"
#include "wdttask.h"
#include "anemometer.h"
#include "rainguage.h"
#include "rxtxtask.h"
#include "version.h"

char		szBuffer[80];

void RxTask(PTASKPARM p)
{
	PRXMSGSTRUCT	pMsgStruct;
	int				valueLen = 0;
	int				i = 0;

	pMsgStruct = (PRXMSGSTRUCT)p;

	if (pMsgStruct->rxErrorCode != 0) {
		txNAK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), pMsgStruct->rxErrorCode);
	}
	else {
		switch (pMsgStruct->frame.cmd) {
			case RX_CMD_AVG_TPH:
				szBuffer[i++] = 'T';
				szBuffer[i++] = ':';

				valueLen = getTemperature(QUERY_TYPE_AVG, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'P';
				szBuffer[i++] = ':';

				valueLen = getPressure(QUERY_TYPE_AVG, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'H';
				szBuffer[i++] = ':';

				valueLen = getHumidity(QUERY_TYPE_AVG, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				// Null terminate string...
				szBuffer[i] = 0;

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_MAX_TPH:
				szBuffer[i++] = 'T';
				szBuffer[i++] = ':';

				valueLen = getTemperature(QUERY_TYPE_MAX, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'P';
				szBuffer[i++] = ':';

				valueLen = getPressure(QUERY_TYPE_MAX, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'H';
				szBuffer[i++] = ':';

				valueLen = getHumidity(QUERY_TYPE_MAX, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				// Null terminate string...
				szBuffer[i] = 0;

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_MIN_TPH:
				szBuffer[i++] = 'T';
				szBuffer[i++] = ':';

				valueLen = getTemperature(QUERY_TYPE_MIN, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'P';
				szBuffer[i++] = ':';

				valueLen = getPressure(QUERY_TYPE_MIN, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'H';
				szBuffer[i++] = ':';

				valueLen = getHumidity(QUERY_TYPE_MIN, &szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				// Null terminate string...
				szBuffer[i] = 0;

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_RESET_MINMAX_TPH:
				resetMinMax();
				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			case RX_CMD_CPU_PERCENTAGE:
				break;

			case RX_CMD_ANEMOMETER:
				break;

			case RX_CMD_RAINGUAGE:
				break;

			case RX_CMD_WDT_DISABLE:
				disableWDTReset();
				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			case RX_CMD_GET_SCHED_VERSION:
				strcpy(szBuffer, getSchedulerVersion());
				i = strlen(szBuffer);
				
				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_GET_AVR_VERSION:
				strcpy(szBuffer, getVersion());
				strcat(szBuffer, " [");
				strcat(szBuffer, getBuildDate());
				strcat(szBuffer, "]");
				i = strlen(szBuffer);
				
				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_PING:
				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			default:
				txNAK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), MSG_NAK_UNKNOWN_CMD);
				break;
		}
	}
}
