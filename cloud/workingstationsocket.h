#ifndef WORKINGSTATIONSOCKET_H
#define WORKINGSTATIONSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QSqlError>
#include <QDateTime>

class WorkingStationSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit WorkingStationSocket(bool isOK, QSqlDatabase &db, QTcpSocket *parent = nullptr);
    ~WorkingStationSocket();


    QSqlQuery *query;
    bool openOK = false;
    bool connectSt = false;

private:
    int getPatientID(const QByteArray &ba);
    QString getTypeHead(char head);
    QByteArray queryData(int patient_ID, const QString &tabelName);   // 查询什么数据 需要什么入口参数呢
    int queryDevIDFromPatientID(int patient_ID);

private slots:
    void slotReadData();

    void responseReq(char pID, const QByteArray &data);

    inline void refreshConnectSt();
    inline void refreshConnectStDiscon();

signals:
    void handled(char pID, const QByteArray &data);

};
#endif // WORKINGSTATIONSOCKET_H
