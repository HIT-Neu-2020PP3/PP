#include <QApplication>
#include <QWidget>
#include "mytcpserver.h"
#include "mytcpclient.h"
#include "deviceclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *mainWin = new QWidget();
    MyTcpServer *newServer = new MyTcpServer(2, 1234);
//    MyTcpClient *newClient = new MyTcpClient(1234);
    DeviceClient *newDC = new DeviceClient(1234);

    mainWin->resize(400, 400);

    mainWin->show();
    return a.exec();
}
