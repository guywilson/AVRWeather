#include <stdint.h>

#ifndef _INCL_SCHEDULER
#define _INCL_SCHEDULER

#define MAX_TASKS           	16

typedef void *					PTASKPARM;

/*
** Define timer type for bit-depth of timer, change this
** if your timer is 64-bit for example...
*/
#ifndef ARCH_SIZE
#define ARCH_SIZE		16
#endif

#if ARCH_SIZE <= 16
typedef uint32_t				timer_t;
#else
typedef uint64_t				timer_t;
#endif

#define MAX_TIMER_VALUE			~((timer_t)0)

/*
 * If, for example, you want a faster interrupt frequency for the
 * RTC tick task, set the prescaler here. If you want the interrupt
 * frequency and clock frequency to be the same, simply set this to 1...
 */
#define RTC_INTERRUPT_PRESCALER			4

/******************************************************************************
**
** The real-time clock interrupt service routing
**
******************************************************************************/
void        _rtcISR();

/******************************************************************************
**
** Get the last recorded CPU percentage
**
******************************************************************************/
int         getCPUPercentage(char * pszBuffer);

/******************************************************************************
**
** The scheduler API
**
******************************************************************************/
void		initScheduler();

void        registerTickTask(void (* tickTask)());

void		registerTask(uint16_t taskID, void (* run)(PTASKPARM));
void		deregisterTask(uint16_t taskID);

void		scheduleTask(uint16_t taskID, timer_t time, PTASKPARM p);
void		rescheduleTask(uint16_t taskID, PTASKPARM p);
void		unscheduleTask(uint16_t taskID);

void		schedule();

#endif
