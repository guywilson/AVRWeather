#include "types.h"

#ifndef _INCL_RXTXTASK
#define _INCL_RXTXTASK

typedef struct {
    decimal24_t     temperature;
    decimal24_t     pressure;
    decimal24_t     humidity;
}
TPH;

typedef struct {
    decimal24_t     avgWindspeed;
    decimal24_t     maxWindspeed;
}
WINDSPEED;

typedef struct {
    decimal24_t     avgRainfall;
    decimal24_t     totalRainfall;
}
RAINFALL;

void RxTask(PTASKPARM p);
void TxTask(PTASKPARM p);

#endif
