#ifndef WORKINGSTATIONSERVER_H
#define WORKINGSTATIONSERVER_H

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

#include "workingstationsocket.h"

class WorkingStationServer : public QWidget
{
    Q_OBJECT
public:
    explicit WorkingStationServer(const QString &username, const QString &pwd,
                                  int maxCon, quint16 port, QWidget *parent = nullptr);

    bool initDB(const QString &username, const QString &pwd);

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

#endif // WORKINGSTATIONSERVER_H
