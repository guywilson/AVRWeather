/******************************************************************************
**
** File: scheduler.c
**
** Description: API functions for the real-time scheduler. Inspired by a
** distant memory of a scheduler I used circa 1996
**
** Copyright: Guy Wilson (c) 2018
**
******************************************************************************/

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "schederr.h"

#define CHECK_TIMER_OVERFLOW
#define TRACK_CPU_PCT

/******************************************************************************
**
** The TASKDEF struct.
**
** Holds the per-task info for the scheduler.
**
******************************************************************************/
typedef struct
{
	uint16_t		ID;				// Unique user-assigned ID
	timer_t			startTime;		// The RTC value when scheduleTask() was callled
	timer_t			scheduledTime;	// The RTC value when the task should run
	timer_t			delay;			// The requested delay (in ms) of when the task should run
	uint8_t			isScheduled;	// Is this task scheduled
	uint8_t			isAllocated;	// Is this allocated to a task
	PTASKPARM		pParameter;		// The parameters to the task
	
	void (* run)(PTASKPARM);		// Pointer to the task function to run
}									// Must be of the form void task(PTASKPARM p);
TASKDEF;

typedef TASKDEF *	PTASKDEF;

TASKDEF						taskDefs[MAX_TASKS];	// Array of tasks for the scheduler
int							taskCount = 0;			// Number of tasks registered

/******************************************************************************
**
** Name: _nullTask()
**
** Description: Null task assigned to TASKDEF entries that are unused.
**
** Parameters:	PTASKPARM	p		Unused.
**
** Returns:		void 
**
******************************************************************************/
void _nullTask(PTASKPARM p)
{
	handleError(ERROR_SCHED_NULLTASKEXEC);
}

/******************************************************************************
**
** Name: _nullTickTask()
**
** Description: Null tick task.
**
** Parameters:	N/A
**
** Returns:		void 
**
******************************************************************************/
void _nullTickTask()
{
	// Do nothing...
}

volatile uint32_t 			_realTimeClock = 0;		// The real time clock counter
volatile uint16_t			_tickCount = 0;			// Num ticks between rtc counts

volatile uint32_t			_busyCount = 0;
volatile uint32_t			_idleCount = 0;
int							_cpuPct = 0;

// The RTC tick task...
void 						(* _tickTask)() = &_nullTickTask;

#ifdef TRACK_CPU_PCT
#define signalBusy()		_busyCount++
#define signalIdle()		_idleCount++

static const char * _szCPUPct[101] = {
	 "0",  "1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",
	"10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
	"20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
	"30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
	"40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
	"50", "51", "52", "53", "54", "55", "56", "57", "58", "59",
	"60", "61", "62", "63", "64", "65", "66", "67", "68", "69",
	"70", "71", "72", "73", "74", "75", "76", "77", "78", "79",
	"80", "81", "82", "83", "84", "85", "86", "87", "88", "89",
	"90", "91", "92", "93", "94", "95", "96", "97", "98", "99",
	"100"
};
#else
#define signalBusy()		// Do nothing
#define signalIdle()		// Do nothing
#endif

/******************************************************************************
**
** Name: _nullTask()
**
** Description: Null task assigned to TASKDEF entries that are unused.
**
** Parameters:	PTASKPARM	p		Unused.
**
** Returns:		void 
**
******************************************************************************/
void _cpuTask(PTASKPARM p)
{
	uint32_t		divisor;

	divisor = _idleCount - _busyCount;

	if (divisor == 0) {
		_cpuPct = 100;
	}
	else {
		_cpuPct = (_busyCount * 100) / divisor;
	}

	// Reset counters...
	_busyCount = 0;
	_idleCount = 0;
}

/******************************************************************************
**
** Name: _rtcISR()
**
** Description: The RTC interrupt handler.
**
** Parameters:	N/A
**
** Returns:		void 
**
******************************************************************************/
void _rtcISR()
{
	_tickCount++;

	if (_tickCount == RTC_INTERRUPT_PRESCALER) {
	    /*
	    ** The RTC is incremented every 1 ms,
		** it is used to drive the real time clock
		** for the scheduler...
	    */
		_realTimeClock++;

		_tickCount = 0;
	}

	/*
	 * Run the tick task, defaults to the nullTick() function.
	 *
	 * This must be a very fast operation, as it is outside of
	 * the scheduler's control. Also, there can be only 1 tick task...
	 */
	signalBusy();
	_tickTask();
}

/******************************************************************************
**
** Name: _getScheduledTime()
**
** Description: Calculates the future RTC value when the task should run
**
** Parameters:
**				timer_t		startTime		The RTC value when called
**				timer_t		requestedDelay	The delay in ms before the task runs
**
** Returns: 
**				timer_t		The future RTC value when the task should run
**
** If we don't care about checking if the timer will overflow, use a macro
** to calculate the default scheduled time (with risk of overflow). 
**
** With a timer incrementing every 1ms:
**
** A 32-bit timer will overflow in approximately 50 days. 
** A 64-bit timer will overflow in approximately 585 million years!
**
******************************************************************************/
#ifdef CHECK_TIMER_OVERFLOW
timer_t _getScheduledTime(timer_t startTime, timer_t requestedDelay)
{
	timer_t			overflowTime;
	
	overflowTime = MAX_TIMER_VALUE - startTime;
	
	if (overflowTime < requestedDelay) {
		return (requestedDelay - overflowTime);
	}
	else {
		return (startTime + requestedDelay);
	}
}
#else
#define _getScheduledTime(startTime, requestedDelay)	(startTime + requestedDelay)
#endif

/******************************************************************************
**
** Public API functions
**
******************************************************************************/

/******************************************************************************
**
** Name: getCPUPercentage()
**
** Description: Returns the last recorded CPU percentage
**
** Parameters:	N/A
**
** Returns:		void 
**
******************************************************************************/
int getCPUPercentage(char * pszBuffer)
{
	int		strLen;

#ifdef TRACK_CPU_PCT
	strLen = (int)strlen(_szCPUPct[_cpuPct]);
	strcpy(pszBuffer, _szCPUPct[_cpuPct]);
#else
	strLen = 2;
	strcpy(pszBuffer, "NA");
#endif
	return strLen;
}

/******************************************************************************
**
** Name: initScheduler()
**
** Description: Initialises the scheduler, must be called before any other
** scheduler API functions.
**
** Parameters:	N/A
**
** Returns:		void 
**
******************************************************************************/
void initScheduler()
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	taskCount = 0;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		td->ID				= 0;
		td->startTime		= 0;
		td->scheduledTime	= 0;
		td->delay			= 0;
		td->isScheduled		= 0;
		td->isAllocated		= 0;
		td->pParameter		= NULL;
		td->run				= &_nullTask;
	}

#ifdef TRACK_CPU_PCT
	registerTask(0x00, &_cpuTask);
	scheduleTask(0x00, 1000, NULL);
#endif
}

/******************************************************************************
**
** Name: registerTickTask()
**
** Description: Registers the scheduler tick task. This tick task is called 
**				from the RTC ISR.
**
** Parameters:	void 	(* tickTask)	Pointer to the tick task function
**
** Returns:		void 
**
******************************************************************************/
void registerTickTask(void (* tickTask)())
{
	_tickTask = tickTask;
}

/******************************************************************************
**
** Name: registerTask()
**
** Description: Registers a task with the scheduler.
**
** Parameters:	uint16_t	taskID		A unique ID for the task
**				void 		(* run)		Pointer to the actual task function
**
** Returns:		void 
**
******************************************************************************/
void registerTask(uint16_t taskID, void (* run)(PTASKPARM))
{
	int			i = 0;
	PTASKDEF	td = NULL;
	uint8_t		noFreeTasks = 1;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (!td->isAllocated) {
			td->ID = taskID;
			td->isAllocated = 1;
			td->run = run;
			taskCount++;
			noFreeTasks = 0;
			break;
		}
	}
    
	if (noFreeTasks) {
		handleError(ERROR_SCHED_NOFREETASKS);
	}
	if (taskCount > MAX_TASKS) {
		handleError(ERROR_SCHED_TASKCOUNTOVERFLOW);
	}
}

/******************************************************************************
**
** Name: deregisterTask()
**
** Description: De-registers a task with the scheduler, freeing up the task
** definition.
**
** Parameters:	uint16_t	taskID		The unique ID for the task
**
** Returns:		void 
**
******************************************************************************/
void deregisterTask(uint16_t taskID)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->ID				= 0;
			td->startTime		= 0;
			td->scheduledTime	= 0;
			td->delay			= 0;
			td->isScheduled		= 0;
			td->isAllocated		= 0;
			td->pParameter		= NULL;
			td->run				= &_nullTask;
			
			taskCount--;
			break;
		}
	}
}

/******************************************************************************
**
** Name: scheduleTask()
**
** Description: Schedules the task to run after the specified delay. A task
** must be registered using registerTask() before it can be scheduled.
**
** Parameters:	
** uint16_t		taskID		The unique ID for the task
** timer_t		time		Number of ms in the future for the task to run
** PTASKPARM	p			Pointer to the task parameters, can be NULL
**
** Returns:		void 
**
******************************************************************************/
void scheduleTask(uint16_t taskID, timer_t time, PTASKPARM p)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->startTime = _realTimeClock;
			td->delay = time;
			td->scheduledTime = _getScheduledTime(td->startTime, td->delay);
			td->isScheduled = 1;
			td->pParameter = p;
			break;
		}
	}
}

/******************************************************************************
**
** Name: rescheduleTask()
**
** Description: Reschedules the task to run again after the same delay as
** specified in the scheduleTask() call. Useful for calling at the end of
** the task itself to force it to run again (after the specified delay).
**
** If you want to reschedule the task to run after a different delay, simply
** call scheduleTask() instead.
**
** Parameters:	
** uint16_t		taskID		The unique ID for the task
** PTASKPARM	p			Pointer to the task parameters, can be NULL
**
** Returns:		void 
**
******************************************************************************/
void rescheduleTask(uint16_t taskID, PTASKPARM p)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->startTime = _realTimeClock;
			td->scheduledTime = _getScheduledTime(td->startTime, td->delay);
			td->isScheduled = 1;
			td->pParameter = p;
			break;
		}
	}
}

/******************************************************************************
**
** Name: unscheduleTask()
**
** Description: Un-schedules a task that has previously been scheduled, e.g. this
** will cancel the scheduled run.
**
** Parameters:	
** uint16_t		taskID		The unique ID for the task
**
** Returns:		void 
**
******************************************************************************/
void unscheduleTask(uint16_t taskID)
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	for (i = 0;i < MAX_TASKS;i++) {
		td = &taskDefs[i];
		
		if (td->ID == taskID) {
			td->startTime = 0;
			td->scheduledTime = 0;
			td->isScheduled = 0;
			td->pParameter = NULL;
			break;
		}
	}
}

/******************************************************************************
**
** Name: schedule()
**
** Description: The main scheduler loop, this will loop forever waiting for 
** tasks to be scheduled. This must be the last function called from main().
**
** Parameters:	N/A
**
** Returns:		it doesn't 
**
******************************************************************************/
void schedule()
{
	int			i = 0;
	PTASKDEF	td = NULL;
	
	/*
	** Scheduler loop, run forever waiting for tasks to be
	** scheduled...
	*/
	while (1) {
		td = &taskDefs[i];
		
		signalIdle();

		if (td->isAllocated) {
			if (td->isScheduled && (_realTimeClock >= td->scheduledTime)) {
				/*
				** Mark the task as un-scheduled, so by default the
				** task will not run again automatically. If the task
				** reschedules itself, this flag will be reset to 1...
				*/
				td->isScheduled = 0;
				
				signalBusy();

				/*
				** Run the task...
				*/
				td->run(td->pParameter);
			}
		}
		
		i++;
		
		if (i == MAX_TASKS) {
			i = 0;
		}
	}
}
