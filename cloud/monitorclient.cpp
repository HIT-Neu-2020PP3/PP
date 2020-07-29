#include "monitorclient.h"

MonitorClient::MonitorClient(quint16 port, QWidget *parent)
    : MyTcpClient(port, parent)
{
    connect(this->mySocket, &QTcpSocket::connected, this, &MonitorClient::tcpConnected);
    connect(this->mySocket, &QTcpSocket::readyRead, this, &MonitorClient::tcpRead);

    connect(this->mySocket, &QTcpSocket::disconnected, this, &MonitorClient::resetStatus);

    connect(this, &MonitorClient::rightSendSignal, this, &MonitorClient::rightSend);
}

bool MonitorClient::isEcgBufferFull()
{
    if ( this->ecgBuffer.size() >= this->ecgBufferSize )
        return true;
    else
        return false;
}

bool MonitorClient::isIbp2BufferFull()
{
    if ( this->ibp2Buffer.size() >= this->ibp2BufferSize )
        return true;
    else
        return false;
}

bool MonitorClient::isSpo2BufferFull()
{
    if ( this->spo2Buffer.size() >= this->spo2BufferSize )
        return true;
    else
        return false;
}

void MonitorClient::packageECG(int data)
{
    if ( isEcgBufferFull() ) {
        emit rightSendSignal(this->ecgBuffer);
        this->ecgBuffer.clear();
        this->ecgBuffer.append((char *)this->dev_id, sizeof(dev_id));
        this->ecgBuffer.append(0x08);
        return;
    }
    char highByte = (char)((data >> 8) & 0xFF);
    char lowByte =(char)(data & 0xFF);
    this->ecgBuffer.append(highByte);
    this->ecgBuffer.append(lowByte);
}

void MonitorClient::packageIBP2(int data)
{
    if ( isIbp2BufferFull() ) {
        emit rightSendSignal(this->ibp2Buffer);
        this->ibp2Buffer.clear();
        this->ibp2Buffer.append((char *)this->dev_id, sizeof(dev_id));
        this->ibp2Buffer.append(0x0a);
    }
    char tmpData = (char)(data & 0xFF);
    this->ibp2Buffer.append(tmpData);
}

void MonitorClient::packageSPO2(int data)
{
    if ( isSpo2BufferFull() ) {
        emit rightSendSignal(this->spo2Buffer);
        this->spo2Buffer.clear();
        this->spo2Buffer.append((char *)this->dev_id, sizeof(dev_id));
        this->spo2Buffer.append(0x09);
    }
    char tmpData = (char)(data & 0xFF);
    this->spo2Buffer.append(tmpData);
}



// 预处理待发送的信息

void MonitorClient::txDataPre(char pID, int data)
{
//    this->mySocket->write(QByteArray(data));
    if ( pID == 0x08 ) { // 心电波形
        packageECG(data);
    } else if ( pID == 0x09 ) {
        packageSPO2(data);
    } else if ( pID = 0x0a ) {
        packageIBP2(data);
    } else
        qDebug()<<"设备端 TCP 数据发送错误";
    qDebug()<<"发送数据";
}

// 处理 TCP 已连接时的动作
void MonitorClient::tcpConnected()
{
    this->connectedStatus = true;
    qDebug()<<"TCP 已连接";
}

void MonitorClient::tcpRead()
{
    qDebug()<<"Client received: "<<this->mySocket->readAll();
}
// 槽函数 用来接收 buffer 数据
void MonitorClient::rightSend(const QByteArray ba)
{
    if ( this->connectedStatus ) {
        this->mySocket->write(ba); // 写数据
        this->mySocket->flush();
        qDebug()<<ba;
    } else
        qDebug()<<"TCP 未连接 发送数据失败";
}

void MonitorClient::resetStatus()
{
    this->connectedStatus = false;
}
