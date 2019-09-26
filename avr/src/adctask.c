#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <scheduler.h>

#include "adctask.h"
#include "taskdef.h"
#include "adc_atmega328p.h"
#include "mbarlookup.h"
#include "humiditylookup.h"
#include "templookup.h"
#include "types.h"

#define MOVING_AVG_ENABLE

uint32_t		conversionCount = 0;

#ifdef MOVING_AVG_ENABLE
uint16_t		adcResults[NUM_ADC_CHANNELS][ADC_RESULT_ARRAY_SIZE];
uint8_t			resultPtr[ADC_RESULT_ARRAY_SIZE];
uint16_t		MAV[NUM_ADC_CHANNELS];
#else
uint16_t		adcResults[NUM_ADC_CHANNELS];
#endif
uint16_t		adcMax[NUM_ADC_CHANNELS];
uint16_t		adcMin[NUM_ADC_CHANNELS];

void resetMinMax()
{
	int		channel;

	for (channel = 0;channel < NUM_ADC_CHANNELS;channel++) {
		adcMin[channel] = 1023;
		adcMax[channel] = 0;
	}
}

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

			if (MAV[channel] > adcMax[channel]) {
				adcMax[channel] = MAV[channel];
			}
			if (MAV[channel] < adcMin[channel]) {
				adcMin[channel] = MAV[channel];
			}
		}

		resultPtr[channel]++;

		if (resultPtr[channel] == ADC_RESULT_ARRAY_SIZE) {
			resultPtr[channel] = 0;
		}
#else
		adcResults[channel] = r->result;

		if (adcResults[channel] > adcMax[channel]) {
			adcMax[channel] = adcResults[channel];
		}
		if (adcResults[channel] < adcMin[channel]) {
			adcMin[channel] = adcResults[channel];
		}
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

uint16_t getADCMax(uint8_t channel)
{
	return adcMax[channel];
}

uint16_t getADCMin(uint8_t channel)
{
	return adcMin[channel];
}

/*
** RH = ((ADC / 1023) - 0.16) / 0.0062
*/
float getHumidity(int queryType)
{
	float		humidity;
	uint16_t	adcValue;
	uint8_t		channel = ADC_CHANNEL0;

	switch (queryType) {
		case QUERY_TYPE_AVG:
			adcValue = getADCAverage(channel);
			break;

		case QUERY_TYPE_MIN:
			adcValue = getADCMin(channel);
			break;

		case QUERY_TYPE_MAX:
			adcValue = getADCMax(channel);
			break;

		default:
			adcValue = getADCAverage(channel);
			break;
	}

	humidity = ((adcValue / 1023) - 0.16) / 0.0062;

	return humidity;
}

/*
** Pmbar = (((adc / 1023) + 0.095) / 0.009) * 10
*/
float getPressure(int queryType)
{
	float		pressure;
	uint16_t	adcValue;
	uint8_t		channel = ADC_CHANNEL1;

	switch (queryType) {
		case QUERY_TYPE_AVG:
			adcValue = getADCAverage(channel);
			break;

		case QUERY_TYPE_MIN:
			adcValue = getADCMin(channel);
			break;

		case QUERY_TYPE_MAX:
			adcValue = getADCMax(channel);
			break;

		default:
			adcValue = getADCAverage(channel);
			break;
	}

	pressure = (((adcValue / 1023) + 0.095) / 0.009) * 10;

	return pressure;
}

/*
** C = (((ADC / 1023) * 5) - 1.375) / 0.0225
*/
float getTemperature(int queryType)
{
	float		temperature;
	int16_t		adcValue;
	uint8_t		channel = ADC_CHANNEL2;

	switch (queryType) {
		case QUERY_TYPE_AVG:
			adcValue = getADCAverage(channel);
			break;

		case QUERY_TYPE_MIN:
			adcValue = getADCMin(channel);
			break;

		case QUERY_TYPE_MAX:
			adcValue = getADCMax(channel);
			break;

		default:
			adcValue = getADCAverage(channel);
			break;
	}
	
	temperature = (((adcValue / 1023) * 5) - 1.375) / 0.0225;

	return temperature;
}
