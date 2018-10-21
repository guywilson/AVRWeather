#ifndef _INCL_RXTXMSGDEF
#define _INCL_RXTXMSGDEF

/******************************************************************************
*
* Message format. Max total message length is 64 bytes
* 
* Offset (HEX)	Offset (DEC)	Length		Description
* ------------	------------	------		-----------------------------------
*   0x00		  0				  1			Start byte (0x3C) '<'
*	0x01		  1				  2			MessageID (16-bit)
*	0x03		  3				  1			Command
*	0x04		  4				  1			Data length (max 58)
*   0x05		  5				 58 (max)	Data
*   0x3F		 63				  1			Finish byte (0x3E) '>'
*
******************************************************************************/
#define COMMAND_PING				0x02
#define COMMAND_WEATHER				0x03
#define COMMAND_LEDON				0x31		// '1'
#define COMMAND_LEDOFF				0x30		// '0'
#define COMMAND_ADC					0x04
#define COMMAND_AVG_WIND_SPEED		0x05
#define COMMAND_MAX_WIND_SPEED		0x06
#define COMMAND_AVG_RAINFALL		0x07
#define COMMAND_MAX_RAINFALL		0x08

#define RESPONSE_ACK				0x41		// 'A'
#define RESPONSE_WEATHER			0x10
#define RESPONSE_ADC				0x11
#define RESPONSE_AVG_WIND_SPEED		0x12
#define RESPONSE_MAX_WIND_SPEED		0x13
#define RESPONSE_AVG_RAINFALL		0x14
#define RESPONSE_MAX_RAINFALL		0x15

#define MSG_START					0x3C		// '<'
#define MSG_FINISH					0x3E		// '>'

#define MAX_DATA_LENGTH				58
#define MAX_PACKET_LENGTH			64

typedef struct
{
	uint16_t	messageID;
	uint8_t		cmd_resp;
	uint8_t		dataLength;
	uint8_t  	data[MAX_DATA_LENGTH]; 
	uint8_t 	errorState;
}
RXTX_CMD;

#endif