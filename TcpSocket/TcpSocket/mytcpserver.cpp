#include "mytcpserver.h"

MyTcpServer::MyTcpServer(int maxCon, quint16 port, QWidget *parent) : QWidget(parent)
{
    // 初始化数据库
    this->initDB();
    this->mTcpServer = new QTcpServer(this);
    this->mTcpServer->setMaxPendingConnections(maxCon); // 最大连接数
    connect(this->mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::tcpNewConnection);

    this->mTcpServer->listen(QHostAddress::Any, port);
}

bool MyTcpServer::initDB()
{
    // 不用设定端口吗 暂时先不用端口看看先
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    // 服务器地址 本地 远程 IP 或者 域名
    this->db.setHostName("localhost");
    // 数据库名
    this->db.setDatabaseName("medical_monitor1");
    // 用户名及密码
    this->db.setUserName("doctor3");
    this->db.setPassword("1234567");
    this->openOK = db.open();
    return this->openOK;
}

void MyTcpServer::tcpNewConnection()
{
    this->mSocket = mTcpServer->nextPendingConnection();
    if (this->mSocket)
    {
        MyTcpSocket *mySocket = new MyTcpSocket(this->openOK, this->db);
        mySocket->setSocketDescriptor(this->mSocket->socketDescriptor());

        // 新建一个线程
        QThread *t = new QThread();
        mySocket->moveToThread(t);
        t->start();

        connect(mySocket, &QTcpSocket::disconnected, this, &MyTcpServer::tcpDisconnect);
        qDebug()<<"TCP 连接成功";
    }
}

void MyTcpServer::tcpDisconnect()
{
    this->mSocket->deleteLater();
    mSocket = 0;
    qDebug()<<"断开连接";
}



