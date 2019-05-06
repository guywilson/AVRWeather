#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "sched/scheduler.h"
#include "sched/schederr.h"
#include "taskdef.h"
#include "heartbeat.h"
#include "adctask.h"
#include "anemometer.h"
#include "rainguage.h"
#include "txtask.h"

#include "led_utils.h"
#include "rtc_atmega328p.h"
#include "adc_atmega328p.h"
#include "serial_atmega328p.h"
#include "extint_atmega328p.h"

#include "pwm_atmega328p.h"

void main(void) __attribute__ ((noreturn));

void setup(void)
{
	setupLEDPin();
	setupRTC();
	setupSerial();
	setupADC();
	setupExtIntInputs();

	// For testing...
	setupPWM();
}

#pragma GCC diagnostic ignored  "-Wmain"
void main(void)
{
	/*
	 * Disable interrupts...
	 */
	cli();

	setup();

	/*
	 * Register RTC tick task...
	 */
	registerTickTask(&readExtIntTask);

	/*
	 * Enable interrupts...
	 */
    sei();
	
	initScheduler();

	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_ADC, &ADCTask);
	registerTask(TASK_ANEMOMETER, &anemometerTask);
	registerTask(TASK_RAINGUAGE, &rainGuageTask);
	registerTask(TASK_TX, &TxTask);

	scheduleTask(
			TASK_HEARTBEAT,
			rtc_val_ms(950),
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
			TASK_TX,
			rtc_val_sec(5),
			NULL);

    /*
     * Trigger the first ADC conversion...
     */
	triggerADC();

	/*
	** Start the scheduler...
	*/
	schedule();
}
