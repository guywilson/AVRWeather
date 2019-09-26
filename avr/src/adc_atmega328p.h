#ifndef _INCL_ADC_ATMEGA328P
#define _INCL_ADC_ATMEGA328P

#define ADC_CHANNEL0				0x00
#define ADC_CHANNEL1				0x01
#define ADC_CHANNEL2				0x02
#define ADC_CHANNEL3				0x03
#define ADC_CHANNEL4				0x04
#define ADC_CHANNEL5				0x05

#ifdef ARDUINO_AVR_NANO
#define ADC_CHANNEL6				0x06
#define ADC_CHANNEL7				0x07

#define NUM_ADC_CHANNELS			8
#else
#define NUM_ADC_CHANNELS			6
#endif

#define ADC_CHANNEL_TEMP			0x08


#define ADC_PRESCALER_DIV2			0x00
#define ADC_PRESCALER_DIV4			0x02
#define ADC_PRESCALER_DIV8			0x03
#define ADC_PRESCALER_DIV16			0x04
#define ADC_PRESCALER_DIV32			0x05
#define ADC_PRESCALER_DIV64			0x06
#define ADC_PRESCALER_DIV128		0x07

#define ADC_BIT_SIZE                10

void setupADC(void);
void triggerADC(void);
void handleADConversionComplete();

#endif
