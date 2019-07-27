#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "exception.h"
#include "framemgr.h"

PFRAME				_pFrameMem = NULL;
int					_size = 0;

FrameManager::FrameManager() : FrameManager(FRAME_MEM_SIZE)
{
}

FrameManager::FrameManager(int size)
{
	if (_pFrameMem == NULL) {
		_size = size;

		_pFrameMem = (PFRAME)malloc(sizeof(FRAME) * _size);

		if (_pFrameMem == NULL) {
			throw new Exception("Failed to allocate frame memory.");
		}

		memset(_pFrameMem, 0, sizeof(FRAME) * _size);
	}
}

FrameManager::~FrameManager()
{
	free(_pFrameMem);
}

int FrameManager::getSize()
{
	return _size;
}

PFRAME FrameManager::allocFrame()
{
	PFRAME 		frame = NULL;
	int			i;

	for (i = 0;i < _size;i++) {
		if (!_pFrameMem[i].isAllocated) {
			frame = &_pFrameMem[i];
			frame->isAllocated = 1;
			break;
		}
	}

	return frame;
}

void FrameManager::freeFrame(PFRAME pFrame)
{
	memset(pFrame, 0, sizeof(FRAME));
}
