#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <scheduler.h>

#include "taskdef.h"

uint32_t _uptimeCounter = 0;

uint32_t getUptime()
{
    return _uptimeCounter;
}

void uptimeTask(PTASKPARM p)
{
    _uptimeCounter++;

    rescheduleTask(TASK_UPTIME, NULL);
}
