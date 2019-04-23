#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "sched/scheduler.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"
#include "mbarlookup.h"
#include "humiditylookup.h"
#include "templookup.h"

#define MOVING_AVG_ENABLE

uint32_t		conversionCount = 0;

#ifdef MOVING_AVG_ENABLE
uint16_t		adcResults[NUM_ADC_CHANNELS][ADC_RESULT_ARRAY_SIZE];
uint8_t			resultPtr[ADC_RESULT_ARRAY_SIZE];
uint16_t		MAV[NUM_ADC_CHANNELS];
#else
uint16_t		adcResults[NUM_ADC_CHANNELS];
#endif

#ifdef MOVING_AVG_ENABLE
void setupADCMAV()
{
	memset(adcResults, 0, (NUM_ADC_CHANNELS * ADC_RESULT_ARRAY_SIZE * sizeof(uint16_t)));

	memset(resultPtr, 0, (ADC_RESULT_ARRAY_SIZE * sizeof(uint8_t)));
	memset(MAV, 0, (NUM_ADC_CHANNELS * sizeof(uint16_t)));
}
#endif

void ADCTask(PTASKPARM p)
{
	PADCRESULT			r =	(PADCRESULT)p;
	uint8_t				channel = r->channel;

#ifdef MOVING_AVG_ENABLE
	uint32_t			avgSum = 0L;
	uint8_t				i = 0;

	if (conversionCount == 0) {
		setupADCMAV();
	}
#endif
	
	/*
	** Recommended that the first conversion result for each channel
	** is ignored as it is likely to be inaccurate...
	*/
	if (conversionCount >= NUM_ADC_CHANNELS) {
#ifdef MOVING_AVG_ENABLE
		adcResults[channel][resultPtr[channel]] = r->result;

		/*
		 * If the results buffer is full, start calculating
		 * the average...
		 */
		if (conversionCount >= ADC_MIN_AVG_CONVERSION_COUNT) {
			for (i = 0;i < ADC_RESULT_ARRAY_SIZE;i++) {
				avgSum += adcResults[channel][i];
			}

			MAV[channel] = (uint16_t)((avgSum >> ADC_RESULT_AVG_SHIFT) & 0xFFFF);
		}

		resultPtr[channel]++;

		if (resultPtr[channel] == ADC_RESULT_ARRAY_SIZE) {
			resultPtr[channel] = 0;
		}
#else
		adcResults[channel] = r->result;
#endif
	}

	conversionCount++;

	/*
	** Trigger next conversion...
	*/
	ADCSRA |= _BV(ADSC);
}

uint16_t getADCAverage(uint8_t channel)
{
#ifdef MOVING_AVG_ENABLE
	return MAV[channel];
#else
	return adcResults[channel];
#endif
}


int getPressure(char * pszDest)
{
	PGM_P		pressure;
	uint16_t	avgPressureADC;
	
	avgPressureADC = getADCAverage(ADC_BAROMETER_CHANNEL) - ADC_MBAR_OFFSET;
	
	memcpy_P(&pressure, &mbarLookup[avgPressureADC], sizeof(PGM_P));
	strcpy_P(pszDest, pressure);
	
	return strlen(pszDest);
}

int getHumidity(char * pszDest)
{
	PGM_P		humidity;
	uint16_t	avgHumidityADC;

	avgHumidityADC = getADCAverage(ADC_HUMIDITY_CHANNEL) - ADC_HUMIDITY_OFFSET;

	memcpy_P(&humidity, &humidityLookup[avgHumidityADC], sizeof(PGM_P));
	strcpy_P(pszDest, humidity);

	return strlen(pszDest);
}

int getTemperature(char * pszDest)
{
	PGM_P			temperature;
	int16_t			avgTempADC;
	
	avgTempADC = getADCAverage(ADC_THERMO_CHANNEL) - ADC_TEMP_OFFSET;
	
	memcpy_P(&temperature, &tempLookup[avgTempADC], sizeof(PGM_P));
	strcpy_P(pszDest, temperature);
	
	return strlen(pszDest);
}
