#include "types.h"

#ifndef _INCL_ANEMOMETER
#define _INCL_ANONOMETER

#define WIND_SPEED_AVG_COUNT			 16
#define WIND_SPEED_AVG_SHIFT			  4

#define ANEMOMETER_CHANNEL				  0

/*
** The diameter of the anemometer blades in metres...
*/
#define BLADE_DIAMETER					 0.1
#define RPS_TO_KPH_SCALE_FACTOR			(11.30973355 * BLADE_DIAMETER)


void		anemometerTask(PTASKPARM p);
uint16_t	getAvgRPS(void);
float       getAvgWindSpeed();
float	    getMaxWindSpeed();

#endif
