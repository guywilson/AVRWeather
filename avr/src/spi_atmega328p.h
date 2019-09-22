#ifndef _INCL_SPI_ATMEGA328P
#define _INCL_SPI_ATMEGA328P

#define TASK_SPI            0x0D00

void		setupSPI();
void		SpiTask(PTASKPARM p);
uint16_t	getCounterValue(int c);
void 		handleSPITransferComplete();

#endif
