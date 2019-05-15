#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "wdt_atmega328p.h"

void __wdtInit(void) __attribute__ ((naked, used, section(".init3")));

void __wdtInit()
{
	cli();

	wdt_reset();

	/*
	 * Clear reset flags...
	 */
	MCUSR &= ~_BV(WDRF);
	WDTCSR |= _BV(WDCE) | _BV(WDE);
	WDTCSR = 0x00;

	sei();
}

/*
 * The watchdog will cause a system reset every 2s unless we
 * reset the timer (see wdtTask())...
 */
void setupWDT()
{
	wdt_reset();

	/*
	 * Clear reset flags...
	 */
	MCUSR &= ~_BV(WDRF);

	/*
	 * Set the Watchdog change enable bit,
	 * and enable the Watchdog system reset mode...
	 */
	WDTCSR |= _BV(WDCE) | _BV(WDE);

	/*
	 * Enable the Watchdog and set prescaler for a 2 sec timeout...
	 */
	WDTCSR = _BV(WDE) | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
}
