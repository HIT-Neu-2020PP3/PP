#include "cloudmonitor.h"

CloudMonitor::CloudMonitor(QWidget *parent): QWidget(parent)
{
    // 得先初始化指针才能再构建信号和槽之间的连接
//    this->initSignalConnection();
}

// 初始化监护仪 这个可以直接放大构造函数里面吗
void CloudMonitor::initMonitor()
{

}

void CloudMonitor::initSerials(const QString &ecgPort, const QString &ibp2Port, const QString &spo2Port)
{
    this->ecgRx = new QWidgetSerialRx(ecgPort);
    this->ibp2Rx = new QWidgetSerialRx(ibp2Port);
    this->spo2Rx = new QWidgetSerialRx(spo2Port);
}
// 初始化TCP客户端
void CloudMonitor::initClient(qint16 port)
{
    this->mClient = new MonitorClient(port);
}
// 初始化界面显示
void CloudMonitor::initDisplayer(int maxEcg, int maxIBP2, int maxSPO2)
{
    this->displayer = new InterfaceDisplay(maxEcg, maxSPO2, maxIBP2);
}

void CloudMonitor::showInterface()
{
    this->displayer->show();
}
// 初始化信号连接
// 这个函数必须放到最后处理了
void CloudMonitor::initSignalConnection()
{
    // 接收到信号时，向画图发送信号
    connect(this->ecgRx, &QWidgetSerialRx::rxDataSignal, this->displayer->ecgDrawer, &QWidgetDrawForSerialRx::refreshFromData);
    connect(this->spo2Rx, &QWidgetSerialRx::rxDataSignal, this->displayer->spo2Drawer, &QWidgetDrawForSerialRx::refreshFromData);
    connect(this->ibp2Rx, &QWidgetSerialRx::rxDataSignal, this->displayer->ibp2Drawer, &QWidgetDrawForSerialRx::refreshFromData);

    // 接收到信号时，向 Socket 发送部分发送信号 参数需要再确定
    // 如果每个串口接收到数据就通过 socket 发送数据 应该不是一个好的选择
    connect(this->ibp2Rx, &QWidgetSerialRx::rxDataSignal, this->mClient, &MonitorClient::txDataPre);
    connect(this->spo2Rx, &QWidgetSerialRx::rxDataSignal, this->mClient, &MonitorClient::txDataPre);
    // 复制有风险 粘贴需谨慎
    connect(this->ecgRx, &QWidgetSerialRx::rxDataSignal, this->mClient, &MonitorClient::txDataPre);
}


