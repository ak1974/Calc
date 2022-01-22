#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H
#include <QQueue>
#include <QVariant>
#include <QMutex>

struct quItem
{
    QVariant operA;
    QVariant operB;
    QVariant typeWork;
    QVariant result;
    int errCode;
    QString mess;

    quItem() {}
    void clear(){ operA.clear(); operB.clear(); typeWork.clear(); result.clear(); errCode=0; mess.clear(); }
    bool isEmpty(){ return operA.isNull() && operB.isNull() && typeWork.isNull(); }
};

class SafeQueue
{
public:
    SafeQueue();

    mutable QMutex mtx;
    void enqueue(quItem itm);
    quItem dequeue();
    int count();

private:

    QQueue<quItem> queue;
};

#endif // SAFEQUEUE_H
