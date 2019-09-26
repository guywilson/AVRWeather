#include "types.h"

#ifndef _INCL_RXTXTASK
#define _INCL_RXTXTASK

typedef struct {
    uint16_t           temperature;
    uint16_t           pressure;
    uint16_t           humidity;
}
TPH;

typedef struct {
    uint16_t           avgWindspeed;
    uint16_t           maxWindspeed;
}
WINDSPEED;

typedef struct {
    uint16_t           avgRainfall;
    uint16_t           totalRainfall;
}
RAINFALL;

void RxTask(PTASKPARM p);
void TxTask(PTASKPARM p);

#endif
