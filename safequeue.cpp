#include "safequeue.h"
#include <QDebug>

SafeQueue::SafeQueue(){}

void SafeQueue::enqueue(quItem itm)
{
    QMutexLocker locker(&mtx);
    queue.enqueue(itm);
}

quItem SafeQueue::dequeue()
{
    quItem qi;
    QMutexLocker locker(&mtx);

    if( !queue.isEmpty() )
        qi = queue.dequeue();

    return qi;
}

int SafeQueue::count()
{
    int cnt;
    QMutexLocker locker(&mtx);
    cnt = queue.count();
    return cnt;
}
