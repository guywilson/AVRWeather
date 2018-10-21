#ifndef _INCL_ADCTASK
#define _INCL_ADCTASK

#define ADC_RESULT_ARRAY_SIZE			8
#define ADC_RESULT_AVG_SHIFT			3

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
