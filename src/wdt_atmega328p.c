#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "sched/scheduler.h"
#include "taskdef.h"
#include "rtc_atmega328p.h"
#include "wdt_atmega328p.h"

void __wdtInit(void) __attribute__((naked)) __attribute__((section(".init3")));

void __wdtInit()
{
	/*
	 * Clear reset flags...
	 */
	MCUSR = 0;
	wdt_disable();
}

/*
 * The watchdog will cause a system reset every 2s unless we
 * reset the timer (see wdtTask())...
 */
void setupWDT()
{
	MCUSR = 0;

	/*
	 * Clear watchdog interrupt
	 * Watchdog change enable
	 * Watchdog enable
	 * Set 2s timeout
	 */
	WDTCSR = _BV(WDIF) | _BV(WDCE) | _BV(WDE) | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
}

void wdtTask(PTASKPARM p)
{
	wdt_reset();

	rescheduleTask(TASK_WDT, NULL);
}
