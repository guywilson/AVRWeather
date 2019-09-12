#include <stdio.h>
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
uint32_t	idleCount = 0;
uint32_t	busyCount = 0;

void RxTask(PTASKPARM p)
{
	PRXMSGSTRUCT	pMsgStruct;
	int				valueLen = 0;
	int				i = 0;
	float			cpuPct = 0.0;

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

			case RX_CMD_RESET_MINMAX:
				resetMinMax();
				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			case RX_CMD_CPU_PERCENTAGE:
				getCPURatio(&idleCount, &busyCount);

				if ((idleCount - busyCount) == 0) {
					strcpy(szBuffer, "N/A");
				}
				else {
					cpuPct = (busyCount * 100.0) / (idleCount - busyCount);
					sprintf(szBuffer, "%.3f", cpuPct);
				}

				i = strlen(szBuffer);

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_WINDSPEED:
				szBuffer[i++] = 'A';
				szBuffer[i++] = ':';

				valueLen = getAvgWindSpeed(&szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'M';
				szBuffer[i++] = ':';

				valueLen = getMaxWindSpeed(&szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				// Null terminate string...
				szBuffer[i] = 0;

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_RAINFALL:
				szBuffer[i++] = 'A';
				szBuffer[i++] = ':';

				valueLen = getAvgRainfall(&szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				szBuffer[i++] = 'T';
				szBuffer[i++] = ':';

				valueLen = getTotalRainfall(&szBuffer[i]);

				szBuffer[i + valueLen] = ';';
				i += valueLen + 1;

				// Null terminate string...
				szBuffer[i] = 0;

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
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
