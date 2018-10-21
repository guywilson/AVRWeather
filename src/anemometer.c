#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "spi_atmega328p.h"
#include "kphlookup.h"
#include "anemometer.h"
#include "taskdef.h"
#include "serial_atmega328p.h"

uint16_t	rpsBuffer[WIND_SPEED_AVG_COUNT];

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
	revolutionsPerSecond = getCounterValue(ANEMOMETER_CHANNEL);

	rpsBuffer[i++] = revolutionsPerSecond;

	if (i == WIND_SPEED_AVG_COUNT) {
		i = 0;
	}

	rescheduleTask(TASK_ANEMOMETER, NULL);
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

int getAvgWindSpeed(char * pszDest)
{
	PGM_P			avgSpeed;
	uint16_t		avgRPS;
	
	avgRPS = getAvgRPS();
	
	if (avgRPS >= KPH_LOOKUP_BUFFER_SIZE) {
		avgRPS = KPH_LOOKUP_BUFFER_SIZE - 1;
	}
	
	memcpy_P(&avgSpeed, &kphLookup[avgRPS], sizeof(PGM_P));
	strcpy_P(pszDest, avgSpeed);
	
	return strlen(pszDest);
}
