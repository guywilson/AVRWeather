#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <scheduler.h>

#include "extint_atmega328p.h"
#include "kphlookup.h"
#include "anemometer.h"
#include "taskdef.h"
#include "serial_atmega328p.h"
#include "types.h"

uint16_t	rpsBuffer[WIND_SPEED_AVG_COUNT];
uint16_t	maxRPS = 0;

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

	if (i == 5) {
		i = 0;
	}

	if (revolutionsPerSecond > maxRPS) {
		maxRPS = revolutionsPerSecond;
	}

	rescheduleTask(TASK_ANEMOMETER, NULL);
}

uint16_t getAvgRPS(void)
{
	int			i;
	uint16_t	avgRPS = 0;

	for (i = 0;i < 5;i++) {
		avgRPS += rpsBuffer[i];
	}

	avgRPS = avgRPS / 5;

	return avgRPS;
}

decimal24_t getAvgWindSpeed()
{
	decimal24_t		avgSpeed;
	uint16_t		avgRPS;
	
	avgRPS = getAvgRPS();
	
	if (avgRPS >= KPH_LOOKUP_BUFFER_SIZE) {
		avgRPS = KPH_LOOKUP_BUFFER_SIZE - 1;
	}
	
	memcpy_P(&avgSpeed, (void *)pgm_read_word(&kphLookup[avgRPS]), sizeof(decimal24_t));
	
	return avgSpeed;
}

decimal24_t getMaxWindSpeed()
{
	decimal24_t		maxSpeed;

	if (maxRPS >= KPH_LOOKUP_BUFFER_SIZE) {
		maxRPS = KPH_LOOKUP_BUFFER_SIZE - 1;
	}

	memcpy_P(&maxSpeed, (void *)pgm_read_word(&kphLookup[maxRPS]), sizeof(decimal24_t));

	return maxSpeed;
}
