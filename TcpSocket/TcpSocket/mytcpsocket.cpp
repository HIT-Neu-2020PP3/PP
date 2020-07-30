#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket(bool openOK, QSqlDatabase &db, QTcpSocket *parent)
    : QTcpSocket(parent), openOK(openOK)
{
    if (openOK)
        this->query = new QSqlQuery(db);

    connect(this, &MyTcpSocket::readyRead, this, &MyTcpSocket::slotReadData);
    connect(this, &MyTcpSocket::handled, this, &MyTcpSocket::responseReq);
}

MyTcpSocket::~MyTcpSocket()
{
    delete this->query;
}

void MyTcpSocket::slotReadData()
{
    // 先只做请求数据库
    QByteArray ba = this->readAll();
    qDebug()<<"slotReadData : receive da "<<ba;

    // 重载这个函数 就可以处理不一样的
    // 在这个socket我们可以做很多事， 我们需要在这里写很多东西，连接之类的

    if (this->openOK)
    {
        QString userid = "d1";
        query->prepare("SELECT * FROM doctors");
//        query->bindValue(":id", userid);
        query->exec();

        // 最后把每一条记录打包起来吗
        // 我觉得是可行的
        qDebug()<<query->size();
        while (query->next()) {
//            qDebug()<<query->value("name")<<query->value("mobile");
            QString name = query->value("name").toString();
            QString mobile = query->value("mobile").toString();
            qDebug()<<name<<mobile;
            // 打包成一个 QByteArray 再发送出去
            QByteArray baa = query->value("name").toByteArray();
            baa.append(query->value("mobile").toByteArray());
            emit handled(baa);
        }

    }
//    emit handled();
}

// 向请求端回写数据
void MyTcpSocket::responseReq(const QByteArray &name)
{
    this->write(name);
    this->flush(); // 立即发送
}
