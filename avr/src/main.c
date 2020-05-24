#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <scheduler.h>
#include <schederr.h>

#include "taskdef.h"
#include "heartbeat.h"
#include "adctask.h"
#include "anemometer.h"
#include "rainguage.h"
#include "rxtxtask.h"
#include "wdttask.h"
#include "uptime.h"

#include "led_utils.h"
#include "rtc_atmega328p.h"
#include "adc_atmega328p.h"
#include "serial_atmega328p.h"
#include "extint_atmega328p.h"
#include "wdt_atmega328p.h"

#include "pwm_atmega328p.h"

//#define TEST_EXTINT

void setup(void)
{
	/*
	 * Disable interrupts...
	 */
	cli();

	setupWDT();

	setupLEDPin();
	setupRTC();
	setupSerial();
	setupADC();
	setupExtIntInputs();

#ifdef TEST_EXTINT
	// For testing...
	setupPWM();
#endif

	/*
	 * Enable interrupts...
	 */
    sei();
}

int main(void)
{
	setup();

	/*
	 * Register RTC tick task...
	 */
	registerTickTask(&readExtIntTask);
	
	/*
	 * Switch on the LED so we know when the board has reset...
	 */
	turnOn(LED_ONBOARD);

	initScheduler(NUM_TASKS);

	registerTask(TASK_WDT, &wdtTask);
	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_ADC, &ADCTask);
	registerTask(TASK_ANEMOMETER, &anemometerTask);
	registerTask(TASK_RAINGUAGE, &rainGuageTask);
	registerTask(TASK_RXCMD, &RxTask);
	registerTask(TASK_UPTIME, &uptimeTask);

	scheduleTask(
			TASK_WDT,
			rtc_val_ms(250),
			NULL);

	scheduleTaskOnce(
			TASK_HEARTBEAT,
			rtc_val_sec(3),
			NULL);

	scheduleTask(
			TASK_ANEMOMETER,
			RTC_ONE_SECOND,
			NULL);

	scheduleTask(
			TASK_RAINGUAGE,
			RTC_ONE_HOUR,
			NULL);

	scheduleTask(
			TASK_UPTIME,
			RTC_ONE_SECOND,
			NULL);

    /*
     * Trigger the first ADC conversion...
     */
	triggerADC();

	/*
	** Start the scheduler...
	*/
	schedule();

	/*
	 * It should never get here...
	 */
	return -1;
}
