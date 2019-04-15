#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

#include "scheduler.h"
#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"
#include "mbarlookup.h"
#include "humiditylookup.h"
#include "templookup.h"

//#define MOVING_AVG_ENABLE

uint8_t			conversionCount = 0;

#ifdef MOVING_AVG_ENABLE
uint16_t		adcResults[NUM_ADC_CHANNELS][ADC_RESULT_ARRAY_SIZE];
uint8_t			resultPtr[NUM_ADC_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};
uint16_t		MAV[NUM_ADC_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};
#else
uint16_t		adcResults[NUM_ADC_CHANNELS];
#endif

void ADCTask(PTASKPARM p)
{
	PADCRESULT			r =		(PADCRESULT)p;
	uint8_t				c;

#ifdef MOVING_AVG_ENABLE
	uint8_t				ptr;
	uint8_t				oldestPtr;
	uint32_t			avgSum;
	uint8_t				i = 0;
#endif

	c	= r->channel;

#ifdef MOVING_AVG_ENABLE
	ptr = resultPtr[c];
	oldestPtr = ptr + 1;

	if (oldestPtr == ADC_RESULT_ARRAY_SIZE) {
		oldestPtr = 0;
	}
#endif
	
	/*
	** Recommended that the first conversion result for each channel
	** is ignored as it is likely to be inaccurate...
	*/
	if (conversionCount < NUM_ADC_CHANNELS) {
		conversionCount++;
	}
	else {
#ifdef MOVING_AVG_ENABLE
		adcResults[c][ptr] = r->result;

		/*
		 * If the results buffer is full, calculate
		 * the first average...
		 */
		if (conversionCount = ADC_MIN_AVG_CONVERSION_COUNT) {
			for (i = 0;i < ADC_RESULT_ARRAY_SIZE;i++) {
				avgSum += adcResults[c][i];
			}

			MAV[c] = (uint16_t)((avgSum >> ADC_RESULT_AVG_SHIFT) & 0xFFFF);
		}
		/*
		 * Calculate the moving average, the most efficient way to do this
		 * is to add the latest reading to the previous moving average and
		 * subtract the oldest reading:
		 *
		 * MAV[n+1] = MAV[n] + result[new] - result[oldest]
		 */
		else if (conversionCount > ADC_MIN_AVG_CONVERSION_COUNT) {
			MAV[c] = MAV[c] + r->result - adcResults[c][oldestPtr];
		}

		resultPtr[c]++;
		
		if (resultPtr[c] == ADC_RESULT_ARRAY_SIZE) {
			resultPtr[c] = 0;
		}
#else
		adcResults[c] = r->result;
#endif
	}

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
	
	avgPressureADC = getADCAverage(ADC_BAROMETER_CHANNEL);
	
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
	
	avgTempADC = getADCAverage(ADC_THERMO_CHANNEL);
	
	memcpy_P(&temperature, &tempLookup[avgTempADC], sizeof(PGM_P));
	strcpy_P(pszDest, temperature);
	
	return strlen(pszDest);
}
