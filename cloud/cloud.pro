QT  += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport sql

HEADERS += \
    monitorclient.h \
    monitorserver.h \
    mytcpclient.h \
    mytcpserver.h \
    mytcpsocket.h

SOURCES += \
    main.cpp \
    monitorclient.cpp \
    monitorserver.cpp \
    mytcpclient.cpp \
    mytcpserver.cpp \
    mytcpsocket.cpp
