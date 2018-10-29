#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
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
#include "error.h"

void main(void) __attribute__ ((noreturn));

void setup(void)
{
	//stop interrupts
	cli();
	
	initScheduler();
	
	registerTask(TASK_HEARTBEAT, &HeartbeatTask);
	registerTask(TASK_ADC, &ADCTask);
	registerTask(TASK_ANEMOMETER, &anemometerTask);
	registerTask(TASK_RAINGUAGE, &rainGuageTask);
	registerTask(TASK_TX, &TxTask);

	registerTickTask(&readExtIntTask);

	setupLEDPin();
	setupRTC();
	setupSerial();
	setupADC();
	setupExtIntInputs();

	//enable interrupts
    sei();
	
    /*
     * Trigger the first conversion...
     */
	triggerADC();
}

#pragma GCC diagnostic ignored  "-Wmain"
void main(void)
{
	setup();
	
	scheduleTask(
			TASK_HEARTBEAT,
			rtc_val_ms(2950),
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
	** Start the scheduler...
	*/
	schedule();
}
