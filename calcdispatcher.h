#ifndef CALCDISPATCHER_H
#define CALCDISPATCHER_H

#include <QObject>
#include <QVariant>
#include "safequeue.h"
#include "computer.h"
#include <QThread>

class CalcDispatcher : public QObject
{
    Q_OBJECT
public:
    explicit CalcDispatcher( QObject *_parent=0 );
    ~CalcDispatcher();

    quItem currentInfo;

    void showRequestInfo();
    void showResultInfo();

    SafeQueue queueRequest;
    SafeQueue queueResult;

    void startThread1();
    void startThread2();

signals:

    void stopProcess();
    void delayChangeSignal(int val);
    void appendQueueItem(const quItem &itm);

public slots:

    void numBtSlot(double val);
    void operBtSlot(const QString &str);
    void calcBtSlot();
    void clearBtSlot();

    void showScreen(const QString &msg);
    void showLog(const QString &msg);

    void queueChanged();

private:

    void showInfo(const quItem &_info);

    Computer *worker1; // Вычисление
    Computer *worker2; // Формирование
};

#endif // CALCDISPATCHER_H
