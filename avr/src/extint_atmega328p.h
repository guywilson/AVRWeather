#ifndef _INCL_EXTINT_ATMEGA328P
#define _INCL_EXTINT_ATMEGA328P

void 		setupExtIntInputs();
void 		resetExtIntPin0Count();
void 		resetExtIntPin1Count();
uint16_t 	getExtIntPin0Count();
uint16_t 	getExtIntPin1Count();
void 		readExtIntTask();

#endif
