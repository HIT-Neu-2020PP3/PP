#ifndef WORKINGSTATIONCLIENT_H
#define WORKINGSTATIONCLIENT_H

#include <QWidget>
#include "mytcpclient.h"

class WorkingStationClient : public MyTcpClient
{
    Q_OBJECT
public:
    explicit WorkingStationClient(quint16 port, QWidget *parent = nullptr);

    void tcpConnected();
    void tcpRead();
    void resetStatus();
//    void processData(char pID, const QByteArray &ba);
//    这个函数不需要在这里做
    // 发送请求
    void queryRequest(int patient_ID, char pID);

    bool connectedStatus = false;

signals:
    void processRxDataSignal(char pID, const QByteArray &ba);

};

#endif // WORKINGSTATIONCLIENT_H
