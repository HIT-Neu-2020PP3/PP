#include "qwidgetserialrx.h"

QWidgetSerialRx::QWidgetSerialRx(const QString &portName, QWidget *parent)
    : QWidget(parent), portName(portName)
{
    if (-1 == this->serialInit())
        return;

    connect(this->com, &QSerialPort::readyRead, this, &QWidgetSerialRx::serialRx);

}

void QWidgetSerialRx::serialRx()
{
//    qDebug()<<"rx: "<< com->readAll();
    // 串口取数 数据处理
    // 循环读数
    while (!com->atEnd())
    {
        QByteArray data = this->com->read(1);
        this->rxDataHandle(data[0]);
    }
}

void QWidgetSerialRx::rxDataHandle(unsigned char data)
{
    // 接收这边 三种数据接收的状态全都放到一起

    // 状态 0 检查数据 ID 决定跳转到不同的状态
    /**************************** ECG ***********************/
    // 状态 1
    // 状态 2
    // 状态 3 校验
    /**************************** IBP2 **********************/
    // 状态 4 接收数据头
    // 状态 5 接收有效数据
    // 状态 6 校验
    /*************************** SPO2 ***********************/
    // 状态 7 接收数据头
    // 状态 8 接收有效数据
    // 状态 9 校验数据
    /**************************** 发送到画图 **********************/


    char tmpData;
    // 最高位为非 0 的数据 复位状态机
    if ( data < 0x80 )
        this->status = 0;

    switch (this->status)
    {
    case 0: // 状态0 接收数据ID
    {
        if ( 0x08 == data )
        {
            this->pkgLen = 7;
            this->status = 1;
            this->pkgDataCnt = 0;
            this->pkgID = data;
//            qDebug("Find ID: 0x%02x", data);
        } else if ( 0x09 == data )
            {
            this->pkgLen = 2;
            this->status = 1;
            this->pkgDataCnt = 0;
            this->pkgID = data;
        } else if ( 0x0a == data )
        {
            this->pkgLen = 2;
            this->status = 1;
            this->pkgDataCnt = 0;
            this->pkgID = data;
        } else
            qDebug()<<"unkonwn ID";
    } break;
    case 1: // 接收数据头
    {
        this->pkgDataHead = data;
        this->status = 2;
    } break;
    case 2: // 接收有效数据
    {
        // 数据缓存
        tmpData = data&0x7F;
        // 从数据头中取出数据的最高位，第 1 个数据的最高位在数据头的最低位中
        tmpData = tmpData | (((this->pkgDataHead >> this->pkgDataCnt)&0x01) << 7 );
        this->pkgData[this->pkgDataCnt] = tmpData;
        this->pkgDataCnt += 1;
        if ( this->pkgDataCnt >= this->pkgLen )
            this->status = 3;
    } break;
    case 3: // 校验数据 这里不做了 直接打印数据
    {
        this->status = 4;
        if (this->pkgID == 0x08) {
        // 校验
            ecg1 = this->pkgData[0];
            ecg1 = ecg1<<8;
            ecg1 = ecg1 + this->pkgData[1];

            ecg2 = this->pkgData[2];
            ecg2 = ecg2<<8;
            ecg2 = ecg2 + this->pkgData[3];

            ecg3 = this->pkgData[4];
            ecg3 = ecg3<<8;
            ecg3 = ecg3 + this->pkgData[5];
            qDebug()<<"ecgRx: ecg ="<< ecg1 <<" ecg2 ="<<ecg2<<" ecg3 ="<<ecg3;
        } else if ( this->pkgID == 0x09 ) {// SPO2
            ecg1 = this->pkgData[0];
            qDebug("SPO2 Rx: spo2 = %d", ecg1);//<<"SPO2 Rx: spo2 ="<< ecg1;
        } else if (this->pkgID == 0x0a ){
            ecg1 = this->pkgData[0];
            qDebug("IBP Rx: ibp2 = %d", ecg1);//<<"IBP Rx: ibp =" << ecg1;
        } else
            qDebug()<<"ERROR!";

        emit rxDataSignal(this->pkgID, ecg1);

    } break;
    case 4: // 发送数据
    {
        // 给出信号
        emit rxDataSignal(this->pkgID, ecg1);
        qDebug()<<"发送信号！！！！！！！！！！！！！！！！";
    }

    }
}

int QWidgetSerialRx::serialInit()
{
    // 查看设备信息
//    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
//    {
//        qDebug() << "Name : " << info.portName();
//        qDebug() << "Description : " << info.description();
//        qDebug() << "Manufacturer: " << info.manufacturer();
//        qDebug() << "Serial Number: " << info.serialNumber();
//    }

    // 创建串口对象
    this->com = new QSerialPort();
    // 打开串口
    this->com->setPortName(portName);
    if (!this->com->open(QIODevice::ReadWrite))
    {
        qDebug()<<"打开串口错误"<<this->com->portName();
        return -1;
    }
    else
        qDebug()<<"打开串口"<<this->com->portName();

    // 配置串口参数
    this->com->setBaudRate(QSerialPort::Baud115200);
    this->com->setDataBits(QSerialPort::Data8);
    this->com->setFlowControl(QSerialPort::NoFlowControl);
    this->com->setParity(QSerialPort::NoParity);
    this->com->setStopBits(QSerialPort::OneStop);

    return 0;
}
