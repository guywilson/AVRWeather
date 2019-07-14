/******************************************************************************
**
** Setup the Watchdog feature on the atmega328p, we use a timeout period of
** 2 seconds, if the Watchdog timer is not reset regularly (by a scheduler
** task), then the Watchdog will reset the device on timeout. This guards
** against program lockup or some erroneous code which stops the scheduler.
**
** BEWARE
** ======
** After scratching my head for a few days wondering why the Watchdog wasn't
** working and my Arduino Nano clone was getting stuck in an endless reset
** loop after the first Watchdog timeout (during testing I deliberately
** disabled the Watchdog timer reset task), I found this post on a thread:
** 		https://forum.arduino.cc/index.php?topic=461948.0
**
** 		The stock Nano bootloader does not correctly handle WDT resets. This is
** 		my recommendation for fixing it:
** 			1. Connect an ISP programmer or Arduino as ISP to your Nano
** 			2. Tools > Programmer > select the correct programmer selection
** 			   for your ISP programmer. Note that if you're using Arduino as
** 			   ISP the correct selection is "Arduino as ISP", not "ArduinoISP".
** 			3. Tools > Board > Arduino/Genuino Uno
** 			4. Tools > Burn Bootloader
** 			5. From now on use the Tools > Board  > Arduino/Genuino Uno
** 			   selection for your Nano, not Tools > Boards > Arduino Nano
**
******************************************************************************/
#include <stdint.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "wdt_atmega328p.h"

/*
 * Tell the linker to put this function in the ".init3" section,
 * this will then be called prior to calling main()...
 */
void __wdtInit(void) __attribute__ ((naked, used, section(".init3")));

void __wdtInit()
{
	cli();

	wdt_reset();

	/*
	 * Clear reset flags...
	 */
	MCUSR &= ~_BV(WDRF);

	/*
	 * Enter Watchdog config mode...
	 */
	WDTCSR |= _BV(WDCE) | _BV(WDE);

	/*
	 * Disable the Watchdog...
	 */
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
	 * Enter Watchdog config mode...
	 */
	WDTCSR |= _BV(WDCE) | _BV(WDE);

	/*
	 * Enable the Watchdog and set prescaler for a 2 sec timeout...
	 */
	WDTCSR = _BV(WDE) | _BV(WDP2) | _BV(WDP1) | _BV(WDP0);
}
