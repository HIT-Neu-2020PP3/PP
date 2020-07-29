#include <QApplication>
#include <QWidget>
#include "mytcpserver.h"
#include "mytcpclient.h"
#include "monitorserver.h"
#include "workingstationserver.h"
#include "workingstationclient.h"
#include "monitorclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget *mainWin = new QWidget();
    QString d1 = "doctor2";
    QString p1 = "123456";
    QString d2 = "doctor3";
    QString p2 = "1234567";

    MonitorServer *newServer = new MonitorServer(d1, p1, 2, 1234);
    MonitorClient *mc = new MonitorClient(1234);

    WorkingStationServer *WSS = new WorkingStationServer(d2, p2, 2, 1235);
    // 这边的 Client 只是用来测试的

    WorkingStationClient *WSC = new WorkingStationClient(1235);
    qDebug("%.2x %.2x", 'Q', 'D');


    mainWin->resize(400, 400);

    mainWin->show();
    return a.exec();
}
