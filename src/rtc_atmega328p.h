#ifndef _INCL_RTC_ATMEGA328P
#define _INCL_RTC_ATMEGA328P

/*
 * Set the RTC interrupt frequency...
 */
#define RTC_INTERRUPT_FREQ				1000


#define RTC_PRESCALER					8

#define CLOCK_DIVISOR					(RTC_INTERRUPT_FREQ * RTC_PRESCALER)


void		setupRTC();
uint32_t	getCurrentTime();

#endif
