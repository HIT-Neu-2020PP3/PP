QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets sql

SOURCES += \
    deviceclient.cpp \
    main.cpp \
    mytcpclient.cpp \
    mytcpserver.cpp \
    mytcpsocket.cpp

HEADERS += \
    deviceclient.h \
    mytcpclient.h \
    mytcpserver.h \
    mytcpsocket.h


