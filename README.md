# AVRWeather

avrw - Real Time Weather Station Controller
-------------------------------------------

Written in C and built using the avr-gcc toolset.

Based around a real-time scheduler, suitable for any number of real-time control systems. The scheduler uses a real-time clock driven by a timer interrupt, in this implementation on the Atmega328p, the real-time clock is incremented every millisecond. The scheduler can handle upto 16 scheduled tasks.

The scheduler API consists of the following functions:

/*  
** Initialise the scheduler  
** Must be called before any other scheduler API functions  
*/  
void initScheduler();

/*  
** Register a task with the scheduler  
** A task must be registered with the scheduler before it can be scheduled  
**  
** taskID			The unique ID of the task  
** ptr_to_task_func	Address of the task function, must be of the form  
**					void task(PTASKPARM) where PTASKPARM is a pointer  
**					to a user defined type defined as void * in scheduler.h  
*/  
void registerTask(uint16_t taskID, ptr_to_task_func(PTASKPARM));

/*  
** De-register a previously registered task  
**  
** taskID			The unique ID of the task  
*/  
void deregisterTask(uint16_t taskID);

/*   
** Schedule a task to run in the specified offset time from now  
** Time is specified in scheduler clock ticks, typically milliseconds  
** but depends on the real-time clock interrupt frequency  
**  
** taskID			The unique ID of the task  
** time				Number of clock ticks from now to run the task  
**					timer_t is system defined as appropriate, e.g. uint32_t  
** task_parms		Pointer to the TASKPARM for the task  
*/  
void scheduleTask(uint16_t taskID, timer_t time, PTASKPARM task_parms);

/*  
** Reschedule a task to run again with the same time delay as  
** specified when scheduled with scheduleTask()  
**  
** taskID			The unique ID of the task  
** task_parms		Pointer to the TASKPARM for the task  
*/  
void rescheduleTask(uint16_t taskID, PTASKPARMS task_parms);

/*  
** Unschedule a previously scheduled task  
**  
** taskID			The unique ID of the task  
*/  
void unscheduleTask(uint16_t taskID);

/*  
** Start the scheduling loop, should never return  
** should be the last call from main()  
*/  
void startScheduler();

The weather station takes inputs from sensors for temperature (ADC), air pressure (ADC), humidity (ADC), wind speed (EXTINT), rainfall (EXTINT).

The weather station controller transmits weather data every 5 seconds over the microcontroller serial port, on an Arduino board, this is typically mapped to a USB port. Format of the weather data is as follows (all data to 2 decimal places):

<t:[temperature in degrees centigrade]><p:[pressure in miilibars]><h:[humidity in % relative humidity]><w:[wind speed in kph]><r:[rainfall in mm/hour]>newline

Example
<t:25.39><p:987.68><h:45.67><w:22.54><r:0.00>newline
