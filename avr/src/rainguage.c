#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <scheduler.h>

#include "extint_atmega328p.h"
#include "rainguage.h"
#include "rainfall.h"
#include "taskdef.h"

uint16_t		tips = 0;
uint16_t		totalTips = 0;

void rainGuageTask(PTASKPARM p)
{
	/*
	** Get number of interrupts (tips) since the last
	** envocation of the task (runs once every hour), from this 
	** we can calculate the rainfall in mm/hour...
	*/
	tips = getExtIntPin1Count();
	
	rescheduleTask(TASK_RAINGUAGE, NULL);
}

int getAvgRainfall(char * pszDest)
{
	PGM_P rainfall;

	if (tips >= RAINFALL_LOOKUP_BUFFER_SIZE) {
		tips = RAINFALL_LOOKUP_BUFFER_SIZE - 1;
	}
	
	memcpy_P(&rainfall, &rainfallLookup[tips], sizeof(PGM_P));
	strcpy_P(pszDest, rainfall);
	
	totalTips += tips;

	/*
	** Reset tips per hour
	*/
	tips = 0;

	return strlen(pszDest);
}

int getTotalRainfall(char * pszDest)
{
	PGM_P rainfall;

	if (totalTips >= RAINFALL_LOOKUP_BUFFER_SIZE) {
		totalTips = RAINFALL_LOOKUP_BUFFER_SIZE - 1;
	}
	
	memcpy_P(&rainfall, &rainfallLookup[totalTips], sizeof(PGM_P));
	strcpy_P(pszDest, rainfall);

	return strlen(pszDest);
}
