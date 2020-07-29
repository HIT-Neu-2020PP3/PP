#ifndef MONITORCLIENT_H
#define MONITORCLIENT_H

#include <QObject>
#include "mytcpclient.h"

class MonitorClient : public MyTcpClient
{
    Q_OBJECT
public:
    explicit MonitorClient(quint16 port, QWidget *parent = nullptr);

    // 判断是否满
    bool isEcgBufferFull();
    bool isIbp2BufferFull();
    bool isSpo2BufferFull();
    // 进行封包
    void packageECG(int data);
    void packageIBP2(int data);
    void packageSPO2(int data);

    // 槽
    // 根据 pID 的不同来选择发送数据
    void txDataPre(char pID, int data);
    void tcpConnected();
    void tcpRead();
    void rightSend(const QByteArray ba);
    void resetStatus();

    bool connectedStatus = false;

    QByteArray ecgBuffer;
    QByteArray ibp2Buffer;
    QByteArray spo2Buffer;

    // 需要发送 dev_id 占两个字节
    // 发送数据表示 一个字节
    short dev_id[1] = { 1 };   // 设备ID 默认为 1 吧
//    QByteArray dev_id_ba = QByteArray(dev_id);
//    QByteArray()
    const int ecgBufferSize = 1003;
    const int ibp2BufferSize = 128;
    const int spo2BufferSize = 251;
signals:
    void rightSendSignal(const QByteArray ba);

};

#endif // MONITORCLIENT_H
