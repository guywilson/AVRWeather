#include <queue>
#include <stdint.h>

#include "frame.h"

using namespace std;

#ifndef _INCL_QUEUEMGR
#define _INCL_QUEUEMGR

class QueueMgr
{
public:
    static QueueMgr & getInstance() {
        static QueueMgr instance;
        return instance;
    }

private:
    QueueMgr();

    queue<TxFrame *>    txQueue;
    queue<RxFrame *>    rxQueue;

    pthread_mutex_t 	txLock;
    pthread_mutex_t 	rxLock;

public:
    ~QueueMgr();
    
    TxFrame *           popTx();
    void                pushTx(TxFrame * pFrame);
    bool                isTxQueueEmpty();

    RxFrame *           popRx();
    void                pushRx(RxFrame * pFrame);
    bool                isRxQueueEmpty();
};

#endif