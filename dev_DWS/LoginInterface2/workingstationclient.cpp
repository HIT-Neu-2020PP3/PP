#include "workingstationclient.h"

WorkingStationClient::WorkingStationClient(quint16 port, QWidget *parent)
    : MyTcpClient(port, parent)
{
    connect(this->mySocket, &QTcpSocket::connected, this, &WorkingStationClient::tcpConnected);
    connect(this->mySocket, &QTcpSocket::readyRead, this, &WorkingStationClient::tcpRead);

    connect(this->mySocket, &QTcpSocket::disconnected, this, &WorkingStationClient::resetStatus);

    //    connect(this, &MonitorClient::rightSendSignal, this, &MonitorClient::rightSend);
}

void WorkingStationClient::tcpConnected()
{
    this->connectedStatus = true;
    qDebug()<<"TCP 已连接";
}

void WorkingStationClient::tcpRead()
{
    // 读取全部数据
    QByteArray ba = this->mySocket->readAll();
    char head = ba.at(0);
    char head2 = ba.at(1);
    ba.remove(0, 2);    // 移除最前面的两个头
    if ( head == head2 ) {// 心电波形
        emit processRxDataSignal(head, ba);
        qDebug()<<"接收数据并发出信号"<<(int)head;
    }
    else {
        qDebug()<<"工作站接收数据错误";
        emit processRxDataSignal(0x00, ba);
    }
}

void WorkingStationClient::resetStatus()
{
    this->connectedStatus = false;
}

// 这是一个槽 可以被其他信号调用
void WorkingStationClient::queryRequest(int patient_ID, char pID)
{
    if ( !this->connectedStatus ) { // 未连接
        qDebug()<<"TCP未连接";
        return;
    }
    QByteArray sendBa;
    sendBa.append("QD");
    char high = (char)(patient_ID >> 8);
    char low = (char)(patient_ID & 0xFF );
    sendBa.append(high);
    sendBa.append(low);
    sendBa.append(pID);
    this->mySocket->write(sendBa); // 虽然这边是立即发送 但是那边不是立即接收啊
    this->mySocket->flush();
}
