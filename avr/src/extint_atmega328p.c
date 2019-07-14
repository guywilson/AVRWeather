#include <stddef.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "rtc_atmega328p.h"

uint16_t intPin0Count = 0;
uint16_t intPin1Count = 0;


void setupExtIntInputs()
{
	/*
	** Set pin D2 (INT0) and D3 (INT1) as inputs...
	*/
	DDRD &= ~(_BV(DDD2) | _BV(DDD3));

	/*
	** Activate the pull-up resistor on pins D2 and D3...
	*/
	PORTD |= _BV(PORTD2) | _BV(PORTD3);

	/*
	** Trigger the interrupts on a falling edge, but don't
	** enable the interrupts. We're going to poll the interrupt
	** flag register instead...
	*/
	EICRA |= 0x0A;
}

void resetExtIntPin0Count()
{
	intPin0Count = 0;
}

void resetExtIntPin1Count()
{
	intPin1Count = 0;
}

uint16_t getExtIntPin0Count()
{
	return intPin0Count;
}

uint16_t getExtIntPin1Count()
{
	return intPin1Count;
}

/*
 * This task is registered as an RTC tick task, e.g. not through the
 * scheduler...
 */
void readExtIntTask()
{
	if (EIFR & 0x01) {
		intPin0Count++;
		EIFR |= 0x01;		// Clear the interrupt flag...
	}
	if (EIFR & 0x02) {
		intPin1Count++;
		EIFR |= 0x02;		// Clear the interrupt flag...
	}
}
