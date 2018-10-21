#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "scheduler.h"
#include "serial_atmega328p.h"
#include "taskdef.h"
#include "adctask.h"
#include "anemometer.h"
#include "rainguage.h"
#include "txtask.h"


void TxTask(PTASKPARM p)
{
	char		szBuffer[64];
	uint8_t		len;
	int			i = 0;

	szBuffer[i++] = '<';
	szBuffer[i++] = 't';
	szBuffer[i++] = ':';
	len = getTemperature(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'p';
	szBuffer[i++] = ':';
	len = getPressure(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'h';
	szBuffer[i++] = ':';
	len = getHumidity(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'w';
	szBuffer[i++] = ':';
	len = getAvgWindSpeed(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;
	
	szBuffer[i++] = '<';
	szBuffer[i++] = 'r';
	szBuffer[i++] = ':';
	len = getRainfall(&szBuffer[i]);
	szBuffer[i + len] = '>';
	i += len + 1;

	szBuffer[i++] = '\n';
	szBuffer[i] = 0;

	txstr(szBuffer, i);
	
	rescheduleTask(TASK_TX, NULL);
}
