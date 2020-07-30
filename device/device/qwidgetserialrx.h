#ifndef QWIDGETSERIALRX_H
#define QWIDGETSERIALRX_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>

class QWidgetSerialRx: public QWidget
{
    Q_OBJECT
public:
    QSerialPort *com;
    char status = 0;
    unsigned char pkgDataCnt;
    unsigned char pkgDataCrc;
    unsigned char pkgData[7];
    unsigned char pkgDataHead;
    unsigned char pkgLen;
    unsigned char pkgID;
    int ecg1, ecg2, ecg3;

    explicit QWidgetSerialRx(const QString &portName, QWidget *parent = nullptr);
    int serialInit();
    void serialRx();
    void rxDataHandle(unsigned char data);
private:
    QString portName;
signals:
    void rxDataSignal(char pID, int data);
};

#endif // QWIDGETSERIALRX_H
