#include <iostream>
#include <queue>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

#include "avrweather.h"
#include "exception.h"
#include "queuemgr.h"

using namespace std;

QueueMgr::QueueMgr()
{
	if (pthread_mutex_init(&txLock, NULL)) {
        throw new Exception("Failed to create TX mutex");
	}

	if (pthread_mutex_init(&rxLock, NULL)) {
        throw new Exception("Failed to create RX mutex");
	}
}

QueueMgr::~QueueMgr()
{
	pthread_mutex_destroy(&txLock);
	pthread_mutex_destroy(&rxLock);
}

TxFrame * QueueMgr::popTx()
{
    TxFrame *     frame = NULL;

	pthread_mutex_lock(&txLock);
    
    if (!txQueue.empty()) {
        frame = txQueue.front();
        txQueue.pop();
    }
	
    pthread_mutex_unlock(&txLock);

    return frame;
}

void QueueMgr::pushTx(TxFrame * pFrame)
{
	pthread_mutex_lock(&txLock);
    txQueue.push(pFrame);
    pthread_mutex_unlock(&txLock);
}

bool QueueMgr::isTxQueueEmpty()
{
    bool    isEmpty;

	pthread_mutex_lock(&txLock);
    isEmpty = txQueue.empty();
    pthread_mutex_unlock(&txLock);

    return isEmpty;
}

RxFrame * QueueMgr::popRx()
{
    RxFrame *     frame = NULL;

	pthread_mutex_lock(&rxLock);
    
    if (!rxQueue.empty()) {
        frame = rxQueue.front();
        rxQueue.pop();
    }
	
    pthread_mutex_unlock(&rxLock);

    return frame;
}

void QueueMgr::pushRx(RxFrame * pFrame)
{
	pthread_mutex_lock(&rxLock);
    rxQueue.push(pFrame);
    pthread_mutex_unlock(&rxLock);
}

bool QueueMgr::isRxQueueEmpty()
{
    bool    isEmpty;

	pthread_mutex_lock(&rxLock);
    isEmpty = rxQueue.empty();
    pthread_mutex_unlock(&rxLock);

    return isEmpty;
}