#include "avrweather.h"

#ifndef _INCL_FRAMEMGR
#define _INCL_FRAMEMGR

#define FRAME_MEM_SIZE				16

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

#endif
