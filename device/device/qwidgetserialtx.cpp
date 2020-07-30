#include "qwidgetserialtx.h"

QWidgetSerialTx::
QWidgetSerialTx(const QString &portName, QWidget *parent)
    : QWidget(parent), portName(portName)
{
    this->serialInit();
}

QWidgetSerialTx::
QWidgetSerialTx(int cycle, const QString &portName, int *source, int sLen, int pkgLen, QWidget *parent)
    : QWidget(parent), portName(portName), pkgLen(pkgLen), dataSource(source), sourceLen(sLen)
{
    this->serialInit();
}


int QWidgetSerialTx::getData()
{
    this->index += 3;

    if (this->index >= this->sourceLen)
        this->index = 0;
    return  this->dataSource[this->index];
}



int QWidgetSerialTx::serialInit()
{
    // 创建串口对象
    this->com = new QSerialPort();
    // 打开串口
    this->com->setPortName(portName);
    if (!this->com->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口错误 "<<portName;
        return -1;
    }
    else
        qDebug()<<"打开串口 "<<portName;

    // 配置串口参数
    this->com->setBaudRate(QSerialPort::Baud115200);
    this->com->setDataBits(QSerialPort::Data8);
    this->com->setFlowControl(QSerialPort::NoFlowControl);
    this->com->setParity(QSerialPort::NoParity);
    this->com->setStopBits(QSerialPort::OneStop);

    return 0;
}
