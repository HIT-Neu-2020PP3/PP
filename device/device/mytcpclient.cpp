#include "mytcpclient.h"

MyTcpClient::MyTcpClient(quint16 port, QWidget *parent) : QWidget(parent), port(port)
{
    this->mySocket = new QTcpSocket(this);
    this->mySocket->connectToHost(QHostAddress::LocalHost, this->port);

    // 设定 Client 定时尝试连接 Server
    this->reConnectTimer = new QTimer(this);
    this->reConnectTimer->start(500);       // 2000ms连接一次

    connect(this->reConnectTimer, &QTimer::timeout, this, &MyTcpClient::reConnect);
    // 这个连接也需要交给子类处理
    // 这个信号吧 需要交给子类处理
//    connect(this->mySocket, &QTcpSocket::readyRead, this, &MyTcpClient::tcpReadyRead);
    connect(this->mySocket, &QTcpSocket::connected, this->reConnectTimer, &QTimer::stop);

    // 处理 Server 先断开连接 尝试重新连接
    connect(this->mySocket, &QTcpSocket::disconnected, this, &MyTcpClient::initTimer);
    // 连接之后的动作交给子类来完成
//    connect(this->mySocket, &QTcpSocket::connected, this, &MyTcpClient::tcpConnect);

}

MyTcpClient::~MyTcpClient()
{
    delete mySocket;
    delete reConnectTimer;
}

// 在这里接收数据 或许可以做一个返回值的操作
void MyTcpClient::tcpReadyRead()
{
    QString re = this->mySocket->readAll();
    qDebug()<<"Client received: "<<re;
//    this->mySocket->readAll().
}

// 尝试重新连接 Server
void MyTcpClient::reConnect()
{
    if (this->mySocket->state() == QAbstractSocket::UnconnectedState)
        this->mySocket->connectToHost(QHostAddress::LocalHost, this->port);
}

// 用来向主机发送数据
void MyTcpClient::sendData()
{
    this->mySocket->write("hello");
}

void MyTcpClient::tcpConnect()
{
    qDebug()<<"Client 连接 Server 成功";
    this->sendData();
}

void MyTcpClient::initTimer()
{
    this->reConnectTimer->start(500);
}
