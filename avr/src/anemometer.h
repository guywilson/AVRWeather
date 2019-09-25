#include "types.h"

#ifndef _INCL_ANEMOMETER
#define _INCL_ANONOMETER

#define WIND_SPEED_AVG_COUNT			 16
#define WIND_SPEED_AVG_SHIFT			  4

#define ANEMOMETER_CHANNEL				  0

void		anemometerTask(PTASKPARM p);
uint16_t	getAvgRPS(void);
decimal24_t getAvgWindSpeed();
decimal24_t	getMaxWindSpeed();

#endif
