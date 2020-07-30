#ifndef TCPSERVER_H
#define TCPSERVER_H

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
#include "mytcpsocket.h"

class MyTcpServer : public QWidget
{
    Q_OBJECT
public:
    explicit MyTcpServer(int maxCon, quint16 port, QWidget *parent = nullptr);

    bool initDB();

private:
    QSqlDatabase db;
    QTcpServer *mTcpServer;
    QTcpSocket *mSocket;

    bool openOK = false;
private slots:
    void tcpNewConnection();

    void tcpDisconnect();

signals:

};

#endif // TCPSERVER_H
