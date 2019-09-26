#include "types.h"

#ifndef _INCL_RAINGUAGE
#define _INCL_RAINGUAGE

#define RAINGUAGE_CHANNEL				 1
#define RAINGUAGE_AVG_COUNT				64

#define PI								3.14159265

#define TIPPING_BUCKET_VOLUME			1750		// In mm^3 (1 cm^3 | 1 ml = 1000mm^3)
#define COLLECTING_FUNNEL_RADIUS		50			// In mm

#define TIPS_TO_MM_SCALE_FACTOR			(TIPPING_BUCKET_VOLUME / (PI * COLLECTING_FUNNEL_RADIUS * COLLECTING_FUNNEL_RADIUS))


void 	    rainGuageTask(PTASKPARM p);
uint16_t    getAvgRainfall();
uint16_t    getTotalRainfall();

#endif