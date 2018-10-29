#ifndef _INCL_RTC_ATMEGA328P
#define _INCL_RTC_ATMEGA328P

//#define TRACK_CPU_PCT

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
 ******************************************************************************
 * DO NOT EDIT!
 ******************************************************************************
 */
#define __RTC_PRESCALER					8
#define __CLOCK_DIVISOR					(RTC_CLOCK_FREQ * RTC_INTERRUPT_PRESCALER * __RTC_PRESCALER)
/*
 ******************************************************************************
 */

/*
 * Convenience macros for scheduler time periods...
 */
#define rtc_val_ms(time_in_ms)				((time_in_ms) * (RTC_CLOCK_FREQ / 1000))

#define rtc_val_sec(time_in_sec)			rtc_val_ms(time_in_sec * 1000)
#define rtc_val_min(time_in_min)			rtc_val_sec(time_in_min * 60)
#define rtc_val_hr(time_in_hr)				rtc_val_min(time_in_hr * 60)

#define RTC_ONE_SECOND						rtc_val_ms(1000)
#define RTC_ONE_MINUTE						rtc_val_ms(60000)
#define RTC_ONE_HOUR						rtc_val_ms(3600000)


void		setupRTC();
uint32_t	getCurrentTime();
void 		registerTickTask(void (* tickTask)());

extern volatile uint32_t _realTimeClock;

#endif
