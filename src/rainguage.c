#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "spi_atmega328p.h"
#include "rainguage.h"
#include "rainfall.h"
#include "taskdef.h"

uint16_t		TPH = 0;

void rainGuageTask(PTASKPARM p)
{
	/*
	** Get number of interrupts (tips) since the last
	** envocation of the task (runs once every hour), from this 
	** we can calculate the rainfall in mm/hour...
	*/
	TPH = getCounterValue(RAINGUAGE_CHANNEL);
	
	rescheduleTask(TASK_RAINGUAGE, NULL);
}

int getRainfall(char * pszDest)
{
	PGM_P rainfall;

	if (TPH >= RAINFALL_LOOKUP_BUFFER_SIZE) {
		TPH = RAINFALL_LOOKUP_BUFFER_SIZE - 1;
	}
	
	memcpy_P(&rainfall, &rainfallLookup[TPH], sizeof(PGM_P));
	strcpy_P(pszDest, rainfall);
	
	return strlen(pszDest);
}
