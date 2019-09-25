#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <scheduler.h>

#include "extint_atmega328p.h"
#include "rainguage.h"
#include "rainfall.h"
#include "taskdef.h"
#include "types.h"

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

decimal24_t getAvgRainfall()
{
	PGM_VOID_P	ptr;
	decimal24_t	rainfall;

	if (tips >= RAINFALL_LOOKUP_BUFFER_SIZE) {
		tips = RAINFALL_LOOKUP_BUFFER_SIZE - 1;
	}
	
	memcpy_P(&ptr, &rainfallLookup[tips], sizeof(PGM_VOID_P));
	memcpy_P(&rainfall, ptr, sizeof(decimal24_t));
	
	totalTips += tips;

	/*
	** Reset tips per hour
	*/
	tips = 0;

	return rainfall;
}

decimal24_t getTotalRainfall()
{
	PGM_VOID_P	ptr;
	decimal24_t rainfall;

	if (totalTips >= RAINFALL_LOOKUP_BUFFER_SIZE) {
		totalTips = RAINFALL_LOOKUP_BUFFER_SIZE - 1;
	}
	
	memcpy_P(&ptr, &rainfallLookup[totalTips], sizeof(PGM_VOID_P));
	memcpy_P(&rainfall, ptr, sizeof(decimal24_t));

	return rainfall;
}
