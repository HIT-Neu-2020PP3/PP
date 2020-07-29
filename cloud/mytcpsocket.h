#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlError>
#include <QDateTime>

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(bool isOK, QSqlDatabase &db, QTcpSocket *parent = nullptr);
    ~MyTcpSocket();




//private:
//    QSqlQueryModel *model;
    QSqlQuery *query;
    bool openOK = false;

private:
   int getDevID(const QByteArray &ba);

   void handleEcg(int dev_id, const QByteArray &ba);
   void handleIBP2(int dev_id, const QByteArray &ba);
   void handleSPO2(int dev_id, const QByteArray &ba);
   bool checkDevExist(int dev_id);

private slots:
    void slotReadData();

    void responseReq(const QByteArray &name);

signals:
    void handled(const QByteArray &name);

};

#endif // MYTCPSOCKET_H
