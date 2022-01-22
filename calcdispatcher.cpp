#include "calcdispatcher.h"
#include <QDebug>
#include <QQueue>

CalcDispatcher::CalcDispatcher(QObject *_parent) : QObject(_parent)
{   
    qRegisterMetaType<quItem>("quItem");

    currentInfo.clear();
    worker1 = 0;
    worker2 = 0;

    startThread1();
    startThread2();
}

CalcDispatcher::~CalcDispatcher()
{
    emit stopProcess();
}

void CalcDispatcher::showScreen(const QString &msg)
{
    qDebug() << __FUNCTION__ << msg;
    QObject *teScreen = this->parent()->findChild<QObject*>("teScreen");
    teScreen->setProperty("text",msg);
}

void CalcDispatcher::showLog(const QString &msg)
{
    qDebug() << __FUNCTION__ << msg;
    QObject *teLog = this->parent()->findChild<QObject*>("teLog");
    teLog->setProperty("text",msg);
}

void CalcDispatcher::queueChanged()
{
    showRequestInfo();
    showResultInfo();
}

void CalcDispatcher::showRequestInfo()
{
    int cnt = queueRequest.count();
    qDebug() << __FUNCTION__ << cnt;
    QObject *textField = this->parent()->findChild<QObject*>("tfReq");
    textField->setProperty("text", QString::number(cnt));
}

void CalcDispatcher::showResultInfo()
{
    int cnt = queueResult.count();
    qDebug() << __FUNCTION__ << cnt;
    QObject *textField = this->parent()->findChild<QObject*>("tfRes");
    textField->setProperty("text", QString::number(cnt));
}

void CalcDispatcher::startThread1()
{
    worker1 = new Computer( &queueRequest, &queueResult, COMP_MODE::REQUEST );
    worker1->setUpdatePeriodSec(1);

    QThread *thread = new QThread;

    worker1->moveToThread(thread);

    connect(thread,SIGNAL(started()), worker1, SLOT(process()) );
    connect(worker1, SIGNAL(finished()), thread, SLOT(quit()) );
    connect(this, SIGNAL(stopProcess()), worker1, SLOT(stopProcess()) );

    connect(worker1, SIGNAL(finished()), worker1, SLOT(deleteLater()) );
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );
    //
    connect(this, SIGNAL(delayChangeSignal(int)), worker1, SLOT(setUpdatePeriodSec(int)) );
    connect(worker1, SIGNAL(queueChange()), this, SLOT(queueChanged()) );

    thread->start();
}

void CalcDispatcher::startThread2()
{
    worker2 = new Computer( &queueRequest, &queueResult, COMP_MODE::RESULT );
    worker2->setUpdatePeriodSec(3);

    QThread *thread = new QThread;

    worker2->moveToThread(thread);

    connect(thread,SIGNAL(started()), worker2, SLOT(process()) );
    connect(worker2, SIGNAL(finished()), thread, SLOT(quit()) );
    connect(this, SIGNAL(stopProcess()), worker2, SLOT(stopProcess()) );

    connect(worker2, SIGNAL(finished()), worker2, SLOT(deleteLater()) );
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()) );
    //
    connect(this, SIGNAL(appendQueueItem(quItem)), worker2, SLOT(appendQueueItem(quItem)) );
    connect(worker2, SIGNAL(errorQuItem(QString)), this, SLOT(showLog(QString)) );
    connect(worker2, SIGNAL(resultQuItem(QString)), this, SLOT(showScreen(QString)) );
    connect(worker2, SIGNAL(resultQuItem(QString)), this, SLOT(showLog(QString)) );
    connect(worker2, SIGNAL(queueChange()), this, SLOT(queueChanged()) );

    thread->start();
}

void CalcDispatcher::numBtSlot(double val)
{
    qDebug() << __FUNCTION__ << val;

    if( currentInfo.typeWork.isNull() ){

        double a = currentInfo.operA.isValid() ? currentInfo.operA.toDouble() : 0;
        currentInfo.operA = a * 10 + val;

    } else {

        double b = currentInfo.operB.isValid() ? currentInfo.operB.toDouble() : 0;
        currentInfo.operB = b * 10 + val;
    }

    currentInfo.result.clear();
    showInfo(currentInfo);
}

void CalcDispatcher::operBtSlot(const QString &str)
{
    qDebug() << __FUNCTION__ << str;
    currentInfo.typeWork = str;
    currentInfo.result.clear();

    showInfo(currentInfo);
}

void CalcDispatcher::calcBtSlot()
{
    qDebug() << __FUNCTION__;
    emit appendQueueItem(currentInfo);
    clearBtSlot();
}

void CalcDispatcher::clearBtSlot()
{
    qDebug() << __FUNCTION__;
    currentInfo.clear();
    showScreen( QString() );
}

void CalcDispatcher::showInfo(const quItem &info)
{
    QString str;

    if( info.operA.isValid() ){
        str += info.operA.toString() + " ";
    }

    if( !info.typeWork.isValid() ) {

        showScreen(str);
        return;

    } else {
        str += info.typeWork.toString() + " ";
    }

    if( info.operB.isValid() ){
        str += info.operB.toString() + " ";
    }

    if( info.result.isValid() ){

        str += "= " + info.result.toString();
    }

    showScreen(str);
}
