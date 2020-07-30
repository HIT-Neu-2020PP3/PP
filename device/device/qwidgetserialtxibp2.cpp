#include "qwidgetserialtxibp2.h"

QWidgetSerialTxIBP2::
QWidgetSerialTxIBP2(int cycle, const QString &portName,
                   int *source, int sLen, QWidget *parent, int pkgLen)
    : QWidgetSerialTx(cycle, portName, source, sLen, pkgLen, parent)
{
    this->pkgID = 0x0a;
    this->timer = new QTimer();
    connect(this->timer, &QTimer::timeout, this, &QWidgetSerialTxIBP2::sendPkg);
    this->timer->start(cycle);
}


void QWidgetSerialTxIBP2::sendPkg()
{
//    this->com->write("hello");
    char *dataBuf;
//    char dataBuf[this->pkgLen];

    dataBuf = this->packageData();

    this->com->write(dataBuf, this->pkgLen);
    delete [] dataBuf;
}


char *QWidgetSerialTxIBP2::packageData()
{
    char *dataBuf = new char[this->pkgLen];

    int ibpData = this->getData();

    char bitH;

    dataBuf[0] = this->pkgID;       // 包 ID
    dataBuf[1] = 0x80;              // 数据头 最高位为 1
    // 只有一个数据
    bitH = (char)(ibpData >> 7);    // 数据高位存入数据头
    dataBuf[1] = dataBuf[1] | (bitH & 0x01);
    dataBuf[2] = 0x80 | ibpData;
    dataBuf[3] = 0xFF;              // 用不到
    dataBuf[4] = 0xFF;              // 用不到
    qDebug()<<"IBP2 Tx:====================";
    return dataBuf;
}
