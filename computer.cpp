#include "computer.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>

Computer::Computer(SafeQueue *sfQuCalc, SafeQueue *sfQuRes, COMP_MODE _mode, QObject *parent) : QObject(parent)
{
    computerMode = _mode;
    queueCalc    = sfQuCalc;
    queueRes     = sfQuRes;
    grabPeriodMls = 1;
    flagStopProcess = false;
}

void Computer::process()
{
    while ( !isStopProcess() ) {

        if( curMode() == REQUEST )
        {
            qDebug() << __FUNCTION__ << REQUEST << delayPeriodMls() << queueCalc->count();
            workForCalc();

        }
        else if(curMode() == RESULT)
        {
            qDebug() << __FUNCTION__ << RESULT << delayPeriodMls() << queueRes->count();
            workForFormAndDisplay();

        }
        else break;

        delayMls(delayPeriodMls());
    }

    emit finished();
}

void Computer::stopProcess()
{
    flagStopProcess = true;
    qDebug() << __FUNCTION__ << flagStopProcess;
}

void Computer::setUpdatePeriodSec(int var)
{
    grabPeriodMls = var * 1000;
}

void Computer::appendQueueItem(const quItem &item)
{
    // проверка

    quItem qi = item;
    bool ok = checkInfo(qi);

    if(!ok){
        emit errorQuItem( qi.mess );
        return;
    }

    // добавление
    queueCalc->enqueue(item);
    emit queueChange();
    emit errorQuItem( infoToString(item));
    emit resultQuItem(infoToString(item));
}

void Computer::delayMls(int mls)
{
    QEventLoop loop;
    QTimer::singleShot(mls, &loop, SLOT(quit()));
    loop.exec();
}

void Computer::workForCalc()
{
    if( queueCalc->count() == 0 ) return;

    quItem qi = queueCalc->dequeue();

    QString sub="-", add="+", mult="x", div="/";

    double a = qi.operA.toDouble();
    double b = qi.operB.toDouble();
    QString func = qi.typeWork.toString();

    int tw = -1;

    if( func == sub )     tw = SUB;
    else if(func == add)  tw = ADD;
    else if(func == mult) tw = MULT;
    else if(func == div)  tw = DIV;

    if( tw < 0 ){
        qi.errCode = BAD_OPERATION;
        queueRes->enqueue(qi);
        return;
    }

    int ok=0;
    CalcLib cl;
    double res= cl.DoIt(tw,a,b,ok);

    qi.errCode = ok;
    qi.result = res;

    queueRes->enqueue(qi);

    emit queueChange();
}

void Computer::workForFormAndDisplay()
{
    if( queueRes->count() == 0 ) return;

    quItem qi = queueRes->dequeue();

    emit queueChange();

    if( qi.errCode == BAD_OPERATION ){

        emit errorQuItem("ERROR: BAD OPERATION.");
        return;
    }
    if( qi.errCode == DIVISION_ZERO ){
        emit errorQuItem("ERROR: DIVISION BY ZERO.");
        return;
    }

    QString str = infoToString(qi);

    emit resultQuItem(str);
}

bool Computer::checkInfo(quItem &_info)
{
    _info.errCode = 1;

    if( !_info.operA.isValid() ){
        _info.mess = "Invalid operand A";
        return false;
    }

    if( !_info.typeWork.isValid() ){
        _info.mess = "Invalid operation.";
        return false;
    }

    if( !_info.operB.isValid() ){
        _info.mess = "Invalid operand B";
        return false;
    }

    _info.errCode = 0;
    return true;
}

QString Computer::infoToString(const quItem &info)
{
    QString str;

    if( info.operA.isValid() ){
        str += info.operA.toString() + " ";
    }

    if( !info.typeWork.isValid() ) {

        return str;
    } else {
        str += info.typeWork.toString() + " ";
    }

    if( info.operB.isValid() ){
        str += info.operB.toString() + " ";
    }

    if( info.result.isValid() ){

        str += "= " + info.result.toString();
    }

    return str;
}

//double Computer::DoIt(int TypeWork, double OperandA, double OperandB, int &errCode)
//{
//    if(OperandB == 0){
//        errCode = DIVISION_ZERO;
//        return 0;
//    }

//    errCode = 0;

//    if( TypeWork == SUB )
//    {
//        return OperandA-OperandB;
//    }
//    else if( TypeWork == ADD )
//    {
//        return OperandA+OperandB;
//    }
//    else if(TypeWork == MULT)
//    {
//        return OperandA*OperandB;
//    }
//    else if(TypeWork == DIV)
//    {
//        return OperandA/OperandB;
//    }

//    errCode = BAD_OPERATION;
//    return 0;
//}
