#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <scheduler.h>

#include "extint_atmega328p.h"
#include "anemometer.h"
#include "taskdef.h"
#include "serial_atmega328p.h"
#include "types.h"

uint16_t	rpsBuffer[WIND_SPEED_AVG_COUNT];
uint16_t	maxRPS = 0;

void resetMaxWindspeed()
{
	maxRPS = 0;
}

void anemometerTask(PTASKPARM p)
{
	static uint8_t		i = 0;
	uint16_t			revolutionsPerSecond;
	
	/*
	** Get number of interrupts (revolutions) since the last
	** envocation of the task (runs once every second), e.g.
	** revolutions per second, from this we can calculate the
	** wind speed. This value is accumulated to calculate the
	** average every 64 seconds...
	*/
	revolutionsPerSecond = getExtIntPin0Count();
	resetExtIntPin0Count();

	rpsBuffer[i++] = revolutionsPerSecond;

	if (i == WIND_SPEED_AVG_COUNT) {
		i = 0;
	}

	if (revolutionsPerSecond > maxRPS) {
		maxRPS = revolutionsPerSecond;
	}
}

uint16_t getAvgRPS(void)
{
	int			i;
	uint16_t	avgRPS = 0;

	for (i = 0;i < WIND_SPEED_AVG_COUNT;i++) {
		avgRPS += rpsBuffer[i];
	}

	avgRPS = avgRPS >> WIND_SPEED_AVG_SHIFT;

	return avgRPS;
}

uint16_t getAvgWindSpeed()
{
	return getAvgRPS();
}

uint16_t getMaxWindSpeed()
{
	return maxRPS;
}
