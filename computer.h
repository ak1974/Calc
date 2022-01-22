#ifndef COMPUTER_H
#define COMPUTER_H

#include <QObject>
#include "safequeue.h"
#include "calclib.h"

enum COMP_MODE {REQUEST, RESULT};
enum ERR_TYPE{ BAD_OPERATION=1, DIVISION_ZERO };
enum OPER{SUB,ADD,MULT,DIV};

class Computer : public QObject
{
    Q_OBJECT
public:
    explicit Computer(SafeQueue *sfQuCalc, SafeQueue *sfQuRes, COMP_MODE _mode, QObject *parent = nullptr);

signals:
    void finished();

    void errorQuItem(const QString &msg);
    void resultQuItem(const QString &msg);

    void queueChange();

public slots:

    void process();
    void stopProcess();

    void setUpdatePeriodSec(int var);

    void appendQueueItem(const quItem &item);


private:
    COMP_MODE computerMode;
    COMP_MODE curMode(){ return computerMode; }

    bool flagStopProcess;
    bool isStopProcess(){ return flagStopProcess; }

    //double DoIt(int TypeWork, double OperandA, double OperandB, int &errCode); // debug

    // 1. Вычисление

    SafeQueue *queueCalc;

    int grabPeriodMls;
    int delayPeriodMls(){ return grabPeriodMls; }

    void delayMls(int mls);
    void workForCalc();

    // 2. Формирование и показ

    SafeQueue *queueRes;

    void workForFormAndDisplay();
    bool checkInfo( quItem &_info);
    QString infoToString(const quItem &info);

};

#endif // COMPUTER_H
