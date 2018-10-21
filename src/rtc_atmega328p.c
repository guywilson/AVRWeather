#include <stdint.h>
#include <avr/interrupt.h>

#define CLOCK_DIVISOR      8000

volatile uint32_t		_realTimeClock = 0L;

void setupRTC()
{
    // Clear registers
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    
    TCNT1  = 0;
    
    /*
    ** Set timer count for 1KHz, e.g 1ms...
    **
    ** Timer value = (clock_speed / (interrupt_freq * pre-scaler)) - 1
    ** Timer value = (16,000,000 / (1000 * 8)) - 1
    */
    OCR1A = (F_CPU / CLOCK_DIVISOR) - 1;

    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    
    // Set CS11 bit for 8 prescaler
    TCCR1B |= (1 << CS11);  
    
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

uint32_t getCurrentTime()
{
	return _realTimeClock;
}

ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
    /*
    ** This interrupt fires every 1 ms,
	** it is used to drive the real time clock
	** for the scheduler...
    */
	_realTimeClock++;
}
