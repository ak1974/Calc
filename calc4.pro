QT += qml quick
CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp \
    calcdispatcher.cpp \
    safequeue.cpp \
    computer.cpp

RESOURCES += qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += /lib

HEADERS += \
    calcdispatcher.h \
    safequeue.h \
    computer.h \

DEFINES +=CALCLIB_LIBRARY

unix:!macx: LIBS += -L$$PWD/lib/ -lcalcLib

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib
