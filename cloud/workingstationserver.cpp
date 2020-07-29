#include "workingstationserver.h"

WorkingStationServer::WorkingStationServer(const QString &username, const QString &pwd, int maxCon, quint16 port, QWidget *parent) : QWidget(parent)
{
    // 初始化数据库
    this->initDB(username, pwd);

    this->mTcpServer = new QTcpServer(this);
    this->mTcpServer->setMaxPendingConnections(maxCon); // 最大连接数
    connect(this->mTcpServer, &QTcpServer::newConnection, this, &WorkingStationServer::tcpNewConnection);

    this->mTcpServer->listen(QHostAddress::Any, port);
}

bool WorkingStationServer::initDB(const QString &username, const QString &pwd)
{
    // 不用设定端口吗 暂时先不用端口看看先
    this->db = QSqlDatabase::addDatabase("QMYSQL");
    // 服务器地址 本地 远程 IP 或者 域名
    this->db.setHostName("localhost");
    // 数据库名
    this->db.setDatabaseName("medical_monitor1");
    // 用户名及密码
    this->db.setUserName(username);
    this->db.setPassword(pwd);
    this->openOK = db.open();
    if ( this->openOK )
        qDebug()<<"Woking Station Server 连接数据库成功";
    return this->openOK;
}

void WorkingStationServer::tcpNewConnection()
{
    this->mSocket = mTcpServer->nextPendingConnection();
    if (this->mSocket)
    {
        WorkingStationSocket *mySocket = new WorkingStationSocket(this->openOK, this->db);
        mySocket->setSocketDescriptor(this->mSocket->socketDescriptor());

        // 新建一个线程
        QThread *t = new QThread();
        mySocket->moveToThread(t);
        t->start();

        connect(mySocket, &QTcpSocket::disconnected, this, &WorkingStationServer::tcpDisconnect);
        qDebug()<<"TCP 连接成功";
    }
}

void WorkingStationServer::tcpDisconnect()
{
    this->mSocket->deleteLater();
    mSocket = 0;
    qDebug()<<"断开连接";
}



