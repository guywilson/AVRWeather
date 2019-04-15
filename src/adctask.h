#include "adc_atmega328p.h"

#ifndef _INCL_ADCTASK
#define _INCL_ADCTASK

#define ADC_RESULT_ARRAY_SIZE			8
#define ADC_RESULT_AVG_SHIFT			3

#define ADC_MIN_AVG_CONVERSION_COUNT	(NUM_ADC_CHANNELS * ADC_RESULT_ARRAY_SIZE) + NUM_ADC_CHANNELS

/*
 * Define which sensor is attached to which channel
 */
#define ADC_HUMIDITY_CHANNEL			ADC_CHANNEL0
#define ADC_BAROMETER_CHANNEL			ADC_CHANNEL1
#define ADC_THERMO_CHANNEL			    ADC_CHANNEL2

typedef struct
{
	uint8_t			channel;
	uint16_t		result;
}
ADCRESULT;

typedef ADCRESULT *		PADCRESULT;

void		ADCTask(PTASKPARM p);
uint16_t	getADCAverage(uint8_t channel);
int 		getPressure(char * pszDest);
int 		getHumidity(char * pszDest);
int 		getTemperature(char * pszDest);

#endif
