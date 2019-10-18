#include "adc_atmega328p.h"
#include "types.h"

#ifndef _INCL_ADCTASK
#define _INCL_ADCTASK

#define ADC_RESULT_ARRAY_SIZE			8
#define ADC_RESULT_AVG_SHIFT			3

#define ADC_MIN_AVG_CONVERSION_COUNT	(NUM_ADC_CHANNELS * ADC_RESULT_ARRAY_SIZE) + NUM_ADC_CHANNELS

#define QUERY_TYPE_AVG					0
#define QUERY_TYPE_MIN					1
#define QUERY_TYPE_MAX					2

/*
 * Define which sensor is attached to which channel
 */
#define ADC_HUMIDITY_CHANNEL			ADC_CHANNEL0
#define ADC_BAROMETER_CHANNEL			ADC_CHANNEL1
#define ADC_THERMO_CHANNEL			    ADC_CHANNEL2

#define getADCBitSize()					((uint8_t)ADC_BIT_SIZE)

typedef struct
{
	uint8_t			channel;
	uint16_t		result;
}
ADCRESULT;

typedef ADCRESULT *		PADCRESULT;

void		resetADCMinMax();
void		ADCTask(PTASKPARM p);
uint16_t	getADCAverage(uint8_t channel);
uint16_t	getADCMax(uint8_t channel);
uint16_t	getADCMin(uint8_t channel);
uint16_t	getPressure(int queryType);
uint16_t	getHumidity(int queryType);
uint16_t	getTemperature(int queryType);

#endif
