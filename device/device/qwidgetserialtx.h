#ifndef QWIDGETSERIALTX_H
#define QWIDGETSERIALTX_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QTimer>

class QWidgetSerialTx : public QWidget
{
    Q_OBJECT
public:
    QSerialPort *com;
    QTimer *timer;

    // 防止隐式转换
    explicit QWidgetSerialTx(const QString &portName, QWidget *parent = nullptr);
    explicit QWidgetSerialTx(int cycle, const QString &portName, int pkgLen = 10, QWidget *parent = nullptr);
    explicit QWidgetSerialTx(int cycle, const QString &portName, int *source, int sLen, int pkgLen, QWidget *parent);

    virtual void sendPkg() = 0;
    int serialInit();
    int getData();
//    ~QWidgetSerialTx() { delete  com; delete timer;};
//private:
    QString portName;
    int pkgLen;
    int *dataSource;
    int sourceLen;
    int index = 0;
    char pkgID;

    virtual char *packageData() = 0;;
signals:

};

#endif // QWIDGETSERIALTX_H
