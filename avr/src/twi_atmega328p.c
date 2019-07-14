#include <stddef.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "scheduler.h"
#include "taskdef.h"

#define SCL_FREQ			100000
#define TWI_PRESCALER		1

#define TWBR_VALUE			((F_CPU / SCL_FREQ) - 16) / (2 * TWI_PRESCALER)

#define MT_STATUS_START_TX		0x08
#define MT_STATUS_START_TX_RP	0x10
#define MT_STATUS_SLAW_TX_ACK	0x18
#define MT_STATUS_SLAW_TX_NACK	0x20
#define MT_STATUS_DATA_TX_ACK	0x28
#define MT_STATUS_DATA_TX_NACK	0x30
#define MT_STATUS_SLAW_LOST		0x38

void setupTWI()
{
	/*
	 * No prescaler
	 */
	TWSR = 0;

	/*
	 * Set the bit rate
	 */
	TWBR = TWBR_VALUE;

	/*
	 * Enable the TWI and the interrupt
	 */
	TWCR = _BV(TWIE) | _BV(TWEN);
}

void startTWI()
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN) | _BV(TWIE);
}

void handleTWI()
{
	uint8_t status = TWSR & 0xF8;

	switch (status) {
		case 0x08:
			break;

		default:
			break;
	}
}
