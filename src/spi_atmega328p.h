#ifndef _INCL_SPI_ATMEGA328P
#define _INCL_SPI_ATMEGA328P

void		setupSPI();
void		SpiTask(PTASKPARM p);
uint16_t	getCounterValue(int c);

#endif