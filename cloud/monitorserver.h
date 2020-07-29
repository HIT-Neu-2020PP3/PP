#ifndef MONITORSERVER_H
#define MONITORSERVER_H

#include <QObject>
#include "mytcpserver.h"

/*
 * 接收设备上传的波形信息的 Server
 *
 *
 *
 *
*/



class MonitorServer : public MyTcpServer
{
    Q_OBJECT
public:
    explicit MonitorServer(int maxCon, quint16 port, QWidget *parent = nullptr);


signals:

};

#endif // MONITORSERVER_H
