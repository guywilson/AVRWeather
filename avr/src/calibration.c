#include <string.h>

#include "calibration.h"

static CALIBRATION_DATA     _calibrationData;
static PCALIBRATION_DATA    pCalibrationData = &_calibrationData;

void readCalibrationData(PCALIBRATION_DATA calibrationData)
{
    memcpy(calibrationData, pCalibrationData, sizeof(CALIBRATION_DATA));
}

void writeCalibrationData(PCALIBRATION_DATA calibrationData)
{
    memcpy(pCalibrationData, calibrationData, sizeof(CALIBRATION_DATA));
}
