#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include <QTimer>

class MyTcpClient : public QWidget
{
    Q_OBJECT
public:
    explicit MyTcpClient(quint16 port, QWidget *parent = nullptr);
    ~MyTcpClient();

private:
    QTcpSocket *mySocket;
    QTimer *reConnectTimer;
//    QTimer *sendTimer;

private slots:
    void tcpReadyRead();

    void reConnect();   // 重新连接 Server

    void sendData();
    void tcpConnect();
    void initTimer();

signals:

};

#endif // MYTCPCLIENT_H
