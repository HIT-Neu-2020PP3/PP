#include "monitortcpsocket.h"

MonitorTcpSocket::MonitorTcpSocket(bool openOK, QSqlDatabase &db, QTcpSocket *parent)
    : QTcpSocket(parent), openOK(openOK)
{
    if (openOK)
        this->query = new QSqlQuery(db);

    connect(this, &MonitorTcpSocket::readyRead, this, &MonitorTcpSocket::slotReadData);
    connect(this, &MonitorTcpSocket::handled, this, &MonitorTcpSocket::responseReq);
}

MonitorTcpSocket::~MonitorTcpSocket()
{
    delete this->query;
}

int MonitorTcpSocket::getDevID(const QByteArray &ba)
{
    char low = ba.at(0);
    char high = ba.at(1);
    int dev_id = high;
    dev_id = dev_id << 8;
    dev_id = dev_id + low;
    return dev_id;
}

void MonitorTcpSocket::handleEcg(int dev_id, const QByteArray &ba)
{
    if ( this->openOK ) {
        qDebug()<<"ECG receive size: "<<ba.size();
        this->query->prepare("INSERT INTO ecg (value, time, dev_id) VALUES (:array, :time, :dev_id)");
        // 与数据库中数据类型一致的十六进制数组

        query->bindValue(":array", ba);
        // 绑定当前时间
        query->bindValue(":time", QDateTime::currentDateTime());
        // 绑定设备ID
        query->bindValue(":dev_id", dev_id);
        bool queryOK = query->exec();
        if ( queryOK ) {
            qDebug()<<"写入 ECG 数据成功";
            this->updateDevState(dev_id);
        } else
            qDebug()<<"写入 ECG 数据失败: "<<this->query->lastError();
    } else
        qDebug()<<"写 ECG 时数据库未开启";
}

// 为什么这个信息无法写入啊
void MonitorTcpSocket::handleIBP2(int dev_id, const QByteArray &ba)
{
    if ( this->openOK ) {
        qDebug()<<"IBP2 receive size: "<<ba.size();
        this->query->prepare("INSERT INTO ibp2 (value, time, dev_id) VALUES (:array, :time, :dev_id)");

        query->bindValue(":array", ba);
        // 绑定当前时间
        query->bindValue(":time", QDateTime::currentDateTime());
        // 绑定设备ID
        query->bindValue(":dev_id", dev_id);
        bool queryOK = query->exec();
        if ( queryOK ) {
            qDebug()<<"写入 IBP2 数据成功";
            this->updateDevState(dev_id);
        } else
            qDebug()<<"写入 IBP2 数据失败: "<<this->query->lastError()<<this->query->lastQuery();
    } else
        qDebug()<<"写 IBP2 时数据库未开启";
}

void MonitorTcpSocket::handleSPO2(int dev_id, const QByteArray &ba)
{
    if ( this->openOK ) {
        qDebug()<<"SPO2 receive size: "<<ba.size();
        this->query->prepare("INSERT INTO spo2 (value, time, dev_id) VALUES (:array, :time, :dev_id)");

        query->bindValue(":array", ba);
        // 绑定当前时间
        query->bindValue(":time", QDateTime::currentDateTime());
        // 绑定设备ID
        query->bindValue(":dev_id", dev_id);
        bool queryOK = query->exec();
        if ( queryOK ) {
            qDebug()<<"写入 SPO2 数据成功";
            this->updateDevState(dev_id);
        } else
            qDebug()<<"写入 SPO2 数据失败: "<<this->query->lastError();
    } else
        qDebug()<<"写 SPO2 时数据库未开启";
}

// 检查当前设备编号是否在设备表中存在
// 假装已经打开数据库了
bool MonitorTcpSocket::checkDevExist(int dev_id)
{
    query->prepare("SELECT * from device "
                  "WHERE dev_id = :dev_id");
    query->bindValue(":dev_id", dev_id);

    if(query->exec())
    {
        if(query->size() > 0)
        {
            query->next();
            qDebug()<<"设备已存在";
            dev_id = query->value("dev_id").toInt();
            qDebug()<<"当前设备编号："<<dev_id;
        }
        else
        {
            query->prepare("INSERT INTO device (dev_id)"
                          "VALUES (:dev_id)");
            query->bindValue(":dev_id", dev_id);
            if (!query->exec())
            {
                qDebug("设备注册失败！");
            }
            else
            {
                qDebug("设备注册成功！");
            }
        }
    }else
    {
        qDebug()<<"查看设备错误";
    }
}

// 更新设备在线状态
void MonitorTcpSocket::updateDevState(int dev_id)
{
    // 每15s更新一次refresh 字段 判定离线条件为refresh时间与当前时间差值超过20s
    this->query->prepare("UPDATE `medical_monitor1`.`device` SET refresh = NOW() WHERE dev_id = :dev_id");
    this->query->bindValue(":dev_id", dev_id);
    bool queryOk = query->exec();
    if(!queryOk)
        qDebug()<<"更新设备在线状态错误";
}

void MonitorTcpSocket::slotReadData()
{
    // 先只做请求数据库
    QByteArray ba = this->readAll();

    if ( ba.size() != 1003 && ba.size() != 251 && ba.size() != 128 ) { // 做一个简单的判断
        qDebug()<<"混乱";
        return;
    }
    // 获取设备 ID
    int dev_id = this->getDevID(ba);
    this->checkDevExist(dev_id);

    // 获取信息类型识别号码
    // 重复的概率比较大
    char packHead = ba.at(2);

    if ( packHead == 0x08) {
        this->handleEcg(dev_id, ba.right(1000));
    } else if ( packHead == 0x09 ) {
        this->handleSPO2(dev_id, ba.right(248));
    } else if ( packHead == 0x0a ) {
        this->handleIBP2(dev_id, ba.right(125));
    } else
        qDebug("接收信息有误");

    qDebug()<<"slotReadData : receive datahead "<<(int)packHead;

    // 就算接收完毕了 这里可以发信号出去
}

// 向请求端回写数据
void MonitorTcpSocket::responseReq(const QByteArray &name)
{

//    this->write(name);
//    this->flush(); // 立即发送
}
