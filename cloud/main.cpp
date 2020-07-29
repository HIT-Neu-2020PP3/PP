#include <QApplication>
#include <QWidget>
#include "mytcpserver.h"
#include "mytcpclient.h"
#include "monitorserver.h"
#include "workingstationserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *mainWin = new QWidget();
    MonitorServer *newServer = new MonitorServer(2, 1234);
//    WorkingStationServer *WSS = new WorkingStationServer(2, 1235);
    // 这边的 Client 只是用来测试的
//    MyTcpClient *newClient = new MyTcpClient(1235);
    qDebug("%.2x %.2x", 'Q', 'D');


    mainWin->resize(400, 400);

    mainWin->show();
    return a.exec();
}
