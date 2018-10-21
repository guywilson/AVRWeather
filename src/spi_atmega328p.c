#include <stddef.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "taskdef.h"

#define NUM_CHANNELS		2

#define REQ_LOW_BYTE		0x10
#define REQ_HIGH_BYTE		0x20

#define DDR_SPI				DDRB
#define DD_MOSI				DDB3
#define DD_SCK				DDB5

uint16_t	counterValue[NUM_CHANNELS] = {0, 0};
uint8_t		channel = 0;
uint8_t		lo_hi = REQ_LOW_BYTE;

void setupSPI()
{
	/*
	** Set MOSI and SCK as output, all others as input...
	*/
	DDR_SPI = _BV(DD_MOSI) | _BV(DD_SCK);
	
	/*
	** Enable the SPI, configure as Master, set clock divider
	** to 16 and enable the SPI interrupt...
	*/
	SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(SPIE);
}

/*
** Send out a channel read request every 500ms, flipping
** between channel 0 & channel 1, so each channel is
** queried every second...
*/
void SpiTask(PTASKPARM p)
{
	/*
	** Request channel value...
	*/
	SPDR = lo_hi | channel;
	
	if (lo_hi == REQ_LOW_BYTE) {
		scheduleTask(TASK_SPI, 5, NULL);
	}
	else {
		scheduleTask(TASK_SPI, 495, NULL);
	}
}

uint16_t getCounterValue(int c)
{
	uint16_t v;
	
	cli();
	
	v = counterValue[c];
	
	sei();
	
	return v;
}

ISR(SPI_STC_vect, ISR_BLOCK)
{
	static uint8_t		lo;
	static uint8_t		hi;
	
	/*
	** Read the counter value...
	*/
	if (lo_hi == REQ_LOW_BYTE) {
		lo_hi = REQ_HIGH_BYTE;
		lo = SPDR;
	}
	else {
		lo_hi = REQ_LOW_BYTE;
		hi = SPDR;
		
		counterValue[channel++] = (((uint16_t)hi) << 8) | lo;
	}
	
	if (channel == NUM_CHANNELS) {
		channel = 0;
	}
}
