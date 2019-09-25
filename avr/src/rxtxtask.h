#include "types.h"

#ifndef _INCL_RXTXTASK
#define _INCL_RXTXTASK

typedef struct {
    decimal24_t     temperature;
    decimal24_t     pressure;
    decimal24_t     humidity;
}
TPH;

void RxTask(PTASKPARM p);
void TxTask(PTASKPARM p);

#endif
