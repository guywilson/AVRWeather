#ifndef _INCL_AVRWEATHER
#define _INCL_AVRWEATHER

/*
** Request frame (6 - 80 bytes)
** <START><LENGTH><MSG_ID><CMD><DATA (0 - 74)><CHECKSUM><END>
**                 |                        |
**                  --included in checksum--
**
** ACK response frame
** <START><LENGTH><MSG_ID><RSP><ACK+DATA  (0 - 73)><CHECKSUM><END>
**
** NAK response frame
** <START><LENGTH><MSG_ID><RSP><NAK+ERR_CODE (2 bytes)><CHECKSUM><END>
**
**
** The checksum is calculated as follows:
**
** The sender adds all the data bytes plus the cmd and msg id, taking
** just the least significant byte and subtracting that from 0xFF gives
** the checksum.
**
** The receiver adds all the data bytes plus the cmd, msg id and checksum,
** the least significant byte should equal 0xFF if the checksum is valid.
*/

#define NUM_REQUEST_FRAME_BYTES		  6
#define MAX_DATA_LENGTH				 74
#define MAX_REQUEST_MESSAGE_LENGTH	(NUM_REQUEST_FRAME_BYTES + MAX_DATA_LENGTH)

#define MAX_CMD_FRAME_LENGTH		 76		// Data + msgID + cmd

#define NAK_FRAME_LEN				   8

#define MSG_CHAR_START				0x7E
#define MSG_CHAR_END				0x81

#define MSG_CHAR_ACK				0x06
#define MSG_CHAR_NAK				0x15

#define MSG_NAK_UNKNOWN_CMD			0x01
#define MSG_NAK_INVALID_CHECKSUM	0x02
#define MSG_NAK_DATA_ERROR			0x04
#define MSG_NAK_DATA_OVERRUN		0x08

#define RX_STATE_START				0x01
#define RX_STATE_LENGTH				0x02
#define RX_STATE_MSGID				0x03
#define RX_STATE_CMD				0x04
#define RX_STATE_DATA				0x05
#define RX_STATE_CHECKSUM			0x06
#define RX_STATE_END				0x07

#define RX_STATE_RESPONSE			0x10
#define RX_STATE_RESPTYPE			0x11
#define RX_STATE_ACK				0x12
#define RX_STATE_NAK				0x13
#define RX_STATE_ERRCODE			0x14

#define RX_CMD_AVG_TPH				0x01
#define RX_CMD_ANEMOMETER			0x02
#define RX_CMD_RAINGUAGE			0x03
#define RX_CMD_MAX_TPH				0x04
#define RX_CMD_MIN_TPH				0x05
#define RX_CMD_RESET_MINMAX_TPH		0x06
#define RX_CMD_PING					0x0F

#define RX_RSP_AVG_TPH				(RX_CMD_AVG_TPH << 4)
#define RX_RSP_ANEMOMETER			(RX_CMD_ANEMOMETER << 4)
#define RX_RSP_RAINGUAGE			(RX_CMD_RAINGUAGE << 4)
#define RX_RSP_MAX_TPH				(RX_CMD_MAX_TPH << 4)
#define RX_RSP_MIN_TPH				(RX_CMD_MIN_TPH << 4)
#define RX_RSP_RESET_MINMAX_TPH		(RX_CMD_RESET_MINMAX_TPH << 4)
#define RX_RSP_PING					(RX_CMD_PING << 4)

#define FRAME_MEM_SIZE				16

typedef struct {
	uint8_t			data[MAX_REQUEST_MESSAGE_LENGTH];
	int				dataLength;

	uint8_t			isAllocated = 0;
}
FRAME;

typedef FRAME *	PFRAME;

typedef struct {
	uint8_t			start;
	uint8_t			frameLength;
	uint8_t			msgID;
	uint8_t			response;
	uint8_t			responseType;

	uint8_t			errorCode;

	uint8_t			data[MAX_DATA_LENGTH];

	uint8_t			checksum;
	uint8_t			end;
}
RXMSGFRAME;

typedef RXMSGFRAME *	PRXMSGFRAME;

typedef struct {
	RXMSGFRAME		frame;

	uint16_t		frameChecksumTotal;
	uint8_t			rxErrorCode;

	time_t			timeStamp;
}
RXMSGSTRUCT;

typedef RXMSGSTRUCT *	PRXMSGSTRUCT;

class FrameManager
{
public:
	static FrameManager & getInstance()
	{
		static FrameManager instance;
		return instance;
	}

private:
	FrameManager();

	PFRAME			_pFrameMem = NULL;
	int				_size;

public:
	FrameManager(int size);
	~FrameManager();

	PFRAME			allocFrame();
	void			freeFrame(PFRAME pFrame);

	int				getSize();
};

uint8_t	getMsgID();
int 	processFrame(PRXMSGSTRUCT pMsg, uint8_t * buffer, int bufferLength);
void	processResponse(uint8_t * response, int responseLength);

#endif
