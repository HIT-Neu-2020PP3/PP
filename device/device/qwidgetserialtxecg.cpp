#include "qwidgetserialtxecg.h"

QWidgetSerialTxEcg::
QWidgetSerialTxEcg(int cycle, const QString &portName,
                   int *source, int sLen, QWidget *parent, int pkgLen)
    : QWidgetSerialTx(cycle, portName, source, sLen, pkgLen, parent)
{
    this->pkgID = 0x08;
    this->timer = new QTimer();
    connect(this->timer, &QTimer::timeout, this, &QWidgetSerialTxEcg::sendPkg);
    this->timer->start(cycle);
}


void QWidgetSerialTxEcg::sendPkg()
{
//    this->com->write("hello");
    char *dataBuf;
//    char dataBuf[this->pkgLen];

    dataBuf = this->packageData();
    this->com->write(dataBuf, this->pkgLen);
    qDebug()<<"ecgTx:*****************************************";
    delete [] dataBuf;
}


char *QWidgetSerialTxEcg::packageData()
{
    char *dataBuf = new char[this->pkgLen];

    int ecgData[3] = {2048, 2048, 2048};
    int i = 0;
    char byteH,  byteL;

    // 取心电数据/获取ADC数据
    ecgData[0] = this->getData();

    // 数据包格式： ID + 数据头 + 数据 + 校验
    // 数据打包
    dataBuf[0] = this->pkgID;  // ID
    dataBuf[1] = 0x80;  // 数据头 最高位总为1
    // 添加数据
    for (; i < 3; i++)
    {

        byteH = (char)(ecgData[i] >> 8);
        byteL = (char)(ecgData[i]&0xFF);
        // 字节最高位存入数据头
        dataBuf[1] = dataBuf[1] | ((byteH&0x80) >> (7 -i*2));
        dataBuf[1] = dataBuf[1] | ((byteL&0x80) >> (7 - i*2 - 1));

        dataBuf[2+i*2] = 0x80 | byteH;
        dataBuf[2+i*2+1] = 0x80 | byteL;
    }
    dataBuf[8] = 0x80; // 暂时用不到
    dataBuf[9] = 0x80; // 暂时不用
    return dataBuf;
}

