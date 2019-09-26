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

uint16_t getAvgRainfall()
{
	totalTips += tips;

	/*
	** Reset tips per hour
	*/
	tips = 0;

	return tips;
}

uint16_t getTotalRainfall()
{
	return totalTips;
}
