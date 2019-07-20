#ifndef _INCL_WDTTASK
#define _INCL_WDTTASK

extern uint8_t			    resetWDT;

#define disableWDTReset()	(resetWDT = 0)

void wdtTask(PTASKPARM p);

#endif
