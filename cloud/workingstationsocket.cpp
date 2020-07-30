#include "workingstationsocket.h"

WorkingStationSocket::WorkingStationSocket(bool openOK, QSqlDatabase &db, QTcpSocket *parent)
    : QTcpSocket(parent), openOK(openOK)
{
    if ( this->openOK )
        this->query = new QSqlQuery(db);
    else
        qDebug()<<"数据库未开启-------";

    connect(this, &WorkingStationSocket::readyRead, this, &WorkingStationSocket::slotReadData);
    connect(this, &WorkingStationSocket::handled, this, &WorkingStationSocket::responseReq);

    connect(this, &WorkingStationSocket::connected, this, &WorkingStationSocket::refreshConnectSt);
    connect(this, &WorkingStationSocket::disconnected, this, &WorkingStationSocket::refreshConnectStDiscon);
}

WorkingStationSocket::~WorkingStationSocket()
{
    delete query;
}

int WorkingStationSocket::getPatientID(const QByteArray &ba)
{
    unsigned char high = ba.at(2);
    unsigned char low = ba.at(3);
    int patient_ID = high;
    patient_ID = patient_ID << 8;
    patient_ID = patient_ID + low;
    qDebug()<<"patient_ID"<<patient_ID;
    return patient_ID;
}

// 获取对应数据表的名字
QString WorkingStationSocket::getTypeHead(char head)
{
    QString typeHead;
    if ( head == 0x08 )
        typeHead = "ecg";
    else if ( head == 0x09 )
        typeHead = "spo2";
    else if ( head == 0x0a )
        typeHead = "ibp2";
    else
        qDebug()<<"未定义数据类型 查询失败";
    return typeHead;
}

// 查询数据表中的内容
QByteArray WorkingStationSocket::queryData(int patient_ID, const QString &tabelName)
{
    // 查询病人对应的设备编号
    int dev_id = this->queryDevIDFromPatientID(patient_ID);
    if ( dev_id == 0 )
        return false;
    QByteArray queryResult; // 查询结果
    // 只查询最新的数据 因此限制 limit 1
    // select value, time  from ecg where dev_id = 1 order by time desc limit 1
    QString queryDataExpression("SELECT value, time FROM ");
    queryDataExpression += tabelName;
    queryDataExpression += " WHERE dev_id = :dev_id ORDER BY time DESC LIMIT 1";
    this->query->prepare(queryDataExpression);
    this->query->bindValue(":dev_id", dev_id);
    if ( !this->query->exec() ) // 查询失败
        qDebug()<<"查询失败"<<this->query->lastError();
    else {
        this->query->next();
        queryResult = this->query->value("value").toByteArray(); // 获得查询的数据
    }
    return queryResult;


}
// 返回查询到的设备ID
// 如果为 0 说明未能获得
int WorkingStationSocket::queryDevIDFromPatientID(int patient_ID)
{
    int q_dev_id = 0;
    if ( this->openOK ) {
        this->query->prepare("SELECT dev_id from medical_monitor1.device_patient where patient_id = :id");
        this->query->bindValue(":id", patient_ID);
        if ( !this->query->exec() )
            qDebug()<<"获取设备 ID 失败 查询不到对应用户的设备"<<query->lastError();
        else {
            this->query->next();
            q_dev_id = this->query->value("dev_id").toInt();
            qDebug()<<"获取设备 ID 成功 dev ID: "<<q_dev_id;
        }
    } else
        qDebug()<<"获取设备 ID 失败 数据库未开启";
    return q_dev_id;    // 返回查询到的设备ID
}

/* 在这里需要处理医生端发来的请求信息
 *      需要约定好数据头：有哪几种请求信息 同时还要能正确的把信息解析出来
 *
*/
void WorkingStationSocket::slotReadData()
{
    QByteArray ba = this->readAll();
    qDebug()<<ba;
    /*
     * 数据定义："QD" + patient_id + head
     *          2   +   2    +  1
     *         0 1     2 3      4
     *                 病人 ID 也会占用两个字节
     */
    // 直接转换成 字符
    QByteArray qD;
    QString requestType = ba.left(2);
    QString tableName;
    char dataTypeHead;
    int patient_id;         // 待请求的设备号码
    if ( requestType == "QD" ) {
        patient_id = this->getPatientID(ba);
        if ( patient_id == 0 ) {
            emit handled(0x00, "bad");
            return;
        }
        dataTypeHead = ba.at(4);
        tableName = this->getTypeHead(dataTypeHead);
        if ( tableName.size() == 0 )
            return;
        qD = this->queryData(patient_id, tableName);    // 获得查询的数据
        if ( qD.size() > 0 )
            emit handled(dataTypeHead, qD);
    } else
        qDebug()<<requestType<<"类型请求赞数无法处理";

}

// 回写数据
void WorkingStationSocket::responseReq(char pID, const QByteArray &data)
{
    // 需要检查 TCP 是否连接
    QByteArray ba;
    // 这次复杂一点 连续两个包的名字
    ba.append(pID);
    ba.append(pID);
    ba.append(data);
    this->write(ba);
    this->flush();  // 立即发送
}

void WorkingStationSocket::refreshConnectSt()
{
    this->connectSt = true;
    qDebug()<<"连接已建立";
}

void WorkingStationSocket::refreshConnectStDiscon()
{
    this->connectSt = false;
    qDebug()<<"连接已经断开";
}
