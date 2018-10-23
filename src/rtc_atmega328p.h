#ifndef _INCL_RTC_ATMEGA328P
#define _INCL_RTC_ATMEGA328P

/*
 * Set the RTC clock frequency to 1KHz (1ms tick). This is a
 * good frequency for the real-time scheduler...
 */
#define RTC_CLOCK_FREQ					1000

/*
 * If, for example, you want a faster interrupt frequency for the
 * RTC tick task, set the prescaler here. If you want the interrupt
 * frequency and clock frequency to be the same, simply set this to 1...
 */
#define RTC_INTERRUPT_PRESCALER			4

/*
 * DO NOT EDIT!
 */
#define __RTC_PRESCALER					8
#define __CLOCK_DIVISOR					(RTC_CLOCK_FREQ * RTC_INTERRUPT_PRESCALER * __RTC_PRESCALER)

#define timer_val(time_in_ms)			(time_in_ms * (RTC_CLOCK_FREQ / 1000))


void		setupRTC();
uint32_t	getCurrentTime();
void 		registerTickTask(void (* tickTask)());

#endif
