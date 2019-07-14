#include <stdint.h>

#include <avr/io.h>

#include "pwm_atmega328p.h"

int16_t		pwmDutyCycle = 16;

void setupPWM(void)
{
	/*
	** Set Port D - Pin 6 as output...
	*/
	DDRD |= _BV(DDD6);

	/*
	** Set initial duty cycle...
	*/
	OCR0A = pwmDutyCycle;
	
	/*
	** Fast PWM mode...
	*/
	TCCR0A |= _BV(COM0A1) | _BV(WGM01) | _BV(WGM00);
	
	/*
	** Divide by 1024 clock prescaler.
	**
	** PWM frequency is calculated by:
	**
	** Clock Freq / (Prescaler * 256)
	*/
	TCCR0B |= _BV(CS02) | _BV(CS00);
}
