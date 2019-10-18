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
#include "uptime.h"
#include "rxtxtask.h"
#include "version.h"

char				szBuffer[80];
uint32_t			idleCount = 0;
uint32_t			busyCount = 0;
uint32_t			messageCount = 0;

TPH_PACKET			tph;
WINDSPEED			ws;
RAINFALL			rf;
DASHBOARD			db;
CPU_RATIO			cpu;

void RxTask(PTASKPARM p)
{
	PRXMSGSTRUCT	pMsgStruct;

	pMsgStruct = (PRXMSGSTRUCT)p;

	if (pMsgStruct->rxErrorCode != 0) {
		txNAK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), pMsgStruct->rxErrorCode);
	}
	else {
		switch (pMsgStruct->frame.cmd) {
			case RX_CMD_TPH:
				tph.current.temperature = getTemperature(QUERY_TYPE_AVG);
				tph.current.pressure = getPressure(QUERY_TYPE_AVG);
				tph.current.humidity = getHumidity(QUERY_TYPE_AVG);

				tph.max.temperature = getTemperature(QUERY_TYPE_MAX);
				tph.max.pressure = getPressure(QUERY_TYPE_MAX);
				tph.max.humidity = getHumidity(QUERY_TYPE_MAX);

				tph.min.temperature = getTemperature(QUERY_TYPE_MIN);
				tph.min.pressure = getPressure(QUERY_TYPE_MIN);
				tph.min.humidity = getHumidity(QUERY_TYPE_MIN);

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)(&tph), sizeof(TPH_PACKET));
				break;

			case RX_CMD_RESET_MINMAX:
				resetADCMinMax();
				resetMaxWindspeed();
				resetTotalRainfall();
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			case RX_CMD_CPU_PERCENTAGE:
				getCPURatio(&cpu);

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)(&cpu), sizeof(CPU_RATIO));
				break;

			case RX_CMD_WINDSPEED:
				ws.avgWindspeed = getAvgWindSpeed();
				ws.maxWindspeed = getMaxWindSpeed();

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)(&ws), sizeof(WINDSPEED));
				break;

			case RX_CMD_RAINFALL:
				rf.avgRainfall = getAvgRainfall();
				rf.totalRainfall = getTotalRainfall();

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)(&rf), sizeof(RAINFALL));
				break;

			case RX_CMD_WDT_DISABLE:
				disableWDTReset();
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			case RX_CMD_GET_DASHBOARD:
				strcpy(db.szAVRVersion, getVersion());
				strcat(db.szAVRVersion, " [");
				strcat(db.szAVRVersion, getBuildDate());
				strcat(db.szAVRVersion, "]");
				strcpy(db.szSchedVersion, getSchedulerVersion());
				strcat(db.szSchedVersion, " [");
				strcat(db.szSchedVersion, getSchedulerBuildDate());
				strcat(db.szSchedVersion, "]");
				
				db.uptime = getUptime();
				db.numMessagesProcessed = messageCount;
				db.numTasksRun = getTaskRunCount();

				txACK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), (uint8_t *)&db, sizeof(DASHBOARD));
				break;

			case RX_CMD_PING:
				txACKStr(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), NULL, 0);
				break;

			default:
				txNAK(pMsgStruct->frame.msgID, (pMsgStruct->frame.cmd << 4), MSG_NAK_UNKNOWN_CMD);
				break;
		}

		messageCount++;
	}
}
