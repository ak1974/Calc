#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include "calcdispatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) return -1;

    QObject *root = engine.rootObjects()[0];

    if( !root ) return -1;

    CalcDispatcher *clDisp = new CalcDispatcher(root);

    QObject::connect(root,SIGNAL(qmlNumBtSignal(double)), clDisp, SLOT(numBtSlot(double)) );
    QObject::connect(root,SIGNAL(qmlOperBtSignal(QString)), clDisp, SLOT(operBtSlot(QString)) );
    QObject::connect(root,SIGNAL(qmlCalcBtSignal()), clDisp, SLOT(calcBtSlot()) );
    QObject::connect(root,SIGNAL(qmlClearBtSignal()), clDisp, SLOT(clearBtSlot()) );
    QObject::connect(root,SIGNAL(qmlSpinDelaySignal(int)), clDisp, SIGNAL(delayChangeSignal(int)));

    return app.exec();
}
