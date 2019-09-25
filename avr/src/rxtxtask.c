#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <scheduler.h>
#include "serial_atmega328p.h"
#include "calibration.h"
#include "taskdef.h"
#include "adctask.h"
#include "wdttask.h"
#include "anemometer.h"
#include "rainguage.h"
#include "rxtxtask.h"
#include "version.h"

char				szBuffer[80];
uint32_t			idleCount = 0;
uint32_t			busyCount = 0;

CALIBRATION_DATA	calibrationData;
TPH					tph;

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
				tph.temperature = getTemperature(QUERY_TYPE_AVG);
				tph.pressure = getPressure(QUERY_TYPE_AVG);
				tph.humidity = getHumidity(QUERY_TYPE_AVG);

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)(&tph), sizeof(TPH));
				break;

			case RX_CMD_MAX_TPH:
				tph.temperature = getTemperature(QUERY_TYPE_MAX);
				tph.pressure = getPressure(QUERY_TYPE_MAX);
				tph.humidity = getHumidity(QUERY_TYPE_MAX);

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)(&tph), sizeof(TPH));
				break;

			case RX_CMD_MIN_TPH:
				tph.temperature = getTemperature(QUERY_TYPE_MIN);
				tph.pressure = getPressure(QUERY_TYPE_MIN);
				tph.humidity = getHumidity(QUERY_TYPE_MIN);

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)(&tph), sizeof(TPH));
				break;

			case RX_CMD_RESET_MINMAX:
				resetMinMax();
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
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

				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
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

				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
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

				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_WDT_DISABLE:
				disableWDTReset();
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			case RX_CMD_GET_SCHED_VERSION:
				strcpy(szBuffer, getSchedulerVersion());
				i = strlen(szBuffer);
				
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_GET_AVR_VERSION:
				strcpy(szBuffer, getVersion());
				strcat(szBuffer, " [");
				strcat(szBuffer, getBuildDate());
				strcat(szBuffer, "]");
				i = strlen(szBuffer);
				
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), szBuffer, i);
				break;

			case RX_CMD_GET_CALIBRATION_DATA:
				readCalibrationData(&calibrationData);
				txACK(
					pMsgStruct->frame.msgID, 
					(pMsgStruct->frame.cmd << 4), 
					(uint8_t *)&calibrationData, 
					sizeof(CALIBRATION_DATA));
				break;

			case RX_CMD_SET_CALIBRATION_DATA:
				memcpy(&calibrationData, pMsgStruct->frame.data, pMsgStruct->frame.cmdFrameLength - 2);

				writeCalibrationData(&calibrationData);

				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			case RX_CMD_PING:
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			default:
				txNAK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), MSG_NAK_UNKNOWN_CMD);
				break;
		}
	}
}
