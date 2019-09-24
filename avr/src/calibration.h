#include <stdint.h>

#ifndef _INCL_CALIBRATION
#define _INCL_CALIBRATION

typedef struct
{
    int16_t         temperatureOffset;
    int16_t         pressureOffset;
    int16_t         humidityOffset;
    int16_t         windOffset;
    int16_t         rainOffset;
}
CALIBRATION_DATA;

typedef CALIBRATION_DATA *     PCALIBRATION_DATA;

void readCalibrationData(PCALIBRATION_DATA calibrationData);
void writeCalibrationData(PCALIBRATION_DATA calibrationData);

#endif