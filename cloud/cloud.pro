QT  += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport sql

HEADERS += \
    monitorclient.h \
    monitorserver.h \
    monitortcpsocket.h \
    mytcpclient.h \
    mytcpserver.h \
    mytcpsocket.h \
    workingstationclient.h \
    workingstationserver.h \
    workingstationsocket.h

SOURCES += \
    main.cpp \
    monitorclient.cpp \
    monitorserver.cpp \
    monitortcpsocket.cpp \
    mytcpclient.cpp \
    mytcpserver.cpp \
    mytcpsocket.cpp \
    workingstationclient.cpp \
    workingstationserver.cpp \
    workingstationsocket.cpp
