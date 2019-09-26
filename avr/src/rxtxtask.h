#include "types.h"

#ifndef _INCL_RXTXTASK
#define _INCL_RXTXTASK

typedef struct {
    float           temperature;
    float           pressure;
    float           humidity;
}
TPH;

typedef struct {
    float           avgWindspeed;
    float           maxWindspeed;
}
WINDSPEED;

typedef struct {
    float           avgRainfall;
    float           totalRainfall;
}
RAINFALL;

void RxTask(PTASKPARM p);
void TxTask(PTASKPARM p);

#endif
