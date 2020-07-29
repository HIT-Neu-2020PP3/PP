#ifndef MONITORSERVER_H
#define MONITORSERVER_H

#include <QObject>
#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QDateTime>
#include "monitortcpsocket.h"

/*
 * 接收设备上传的波形信息的 Server
 *
 *
 *
 *
*/

class MonitorServer : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorServer(int maxCon, quint16 port, QWidget *parent = nullptr);

    bool initDB();

//private:
    QSqlDatabase db;
    QTcpServer *mTcpServer;
    QTcpSocket *mSocket;

    bool openOK = false;
//private slots:
    void tcpNewConnection();

    void tcpDisconnect();

signals:

};


#endif // MONITORSERVER_H
