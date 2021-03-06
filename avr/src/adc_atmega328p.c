#include <avr/io.h>
#include <avr/interrupt.h>
#include <scheduler.h>

#include "rtc_atmega328p.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"

static ADCRESULT			adcr;

void setupADC(void)
{
	ADMUX	= _BV(REFS0) | ADC_CHANNEL0;
	ADCSRA	= _BV(ADEN) | _BV(ADIE) | ADC_PRESCALER_DIV128;

	resetADCMinMax();
}

void triggerADC(void)
{
	/*
	** Trigger first conversion...
	*/
	ADCSRA |= _BV(ADSC);
}

/*
** ADC Conversion complete interrupt handler
*/
void handleADConversionComplete()
{
	uint8_t				channel;
	uint16_t			low;
	uint16_t			high;
	
	/*
	** 10-bit result from ADC
	** Read LSB first then MSB
	*/
	channel	= ADMUX & 0x07;
	low		= ADCL;
	high	= ADCH & 0x03;

	adcr.channel = channel;
	adcr.result = (high << 8) | low;

	/*
	** Increment Channel for next conversion...
	*/
	ADMUX++;
	
	if ((ADMUX & 0x07) == NUM_ADC_CHANNELS - 1) {
		ADMUX &= 0xF8;
	}

	/*
	** Each channel will process a result every 15 ms
	** This will fill the moving average buffer for each 
	** channel every second...
	*/
	scheduleTaskOnce(TASK_ADC, rtc_val_ms(15), (PTASKPARM)&adcr);
}
