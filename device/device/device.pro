QT  += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport sql

SOURCES += \
    cloudmonitor.cpp \
    interfacedisplay.cpp \
    main.cpp \
    monitorclient.cpp \
    mytcpclient.cpp \
    qwidgetdraw.cpp \
    qwidgetdrawforserialrx.cpp \
    qwidgetserialrx.cpp \
    qwidgetserialtx.cpp \
    qwidgetserialtxecg.cpp \
    qwidgetserialtxibp2.cpp \
    qwidgetserialtxspo2.cpp

HEADERS += \
    cloudmonitor.h \
    interfacedisplay.h \
    monitorclient.h \
    mytcpclient.h \
    qwidgetdraw.h \
    qwidgetdrawforserialrx.h \
    qwidgetserialrx.h \
    qwidgetserialtx.h \
    qwidgetserialtxecg.h \
    qwidgetserialtxibp2.h \
    qwidgetserialtxspo2.h \
    wavedata.h
