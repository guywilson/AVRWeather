#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <avr/wdt.h>

#include <scheduler.h>
#include "taskdef.h"
#include "wdttask.h"

uint8_t						resetWDT = 1;

/*
** Reset the watchdog timer every 250ms, if the program fails
** and the scheduler stops, this will not be called and the
** watchdog timer will reset the device...
*/
void wdtTask(PTASKPARM p)
{
	if (resetWDT) {
		wdt_reset();
	}

	rescheduleTask(TASK_WDT, NULL);
}
