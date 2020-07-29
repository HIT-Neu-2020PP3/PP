#include "interfacedisplay.h"

InterfaceDisplay::InterfaceDisplay(QWidget *parent) : QWidget(parent)
{

}

InterfaceDisplay::InterfaceDisplay(int maxE, int maxS, int maxI, QWidget *parent):
    QWidget(parent), maxEcg(maxE), maxSPO2(maxS), maxIBP2(maxI)
{
    this->ecgDrawer = new QWidgetDrawForSerialRx(this->maxEcg);
    this->ibp2Drawer = new QWidgetDrawForSerialRx(this->maxIBP2);
    this->spo2Drawer = new QWidgetDrawForSerialRx(this->maxSPO2);

    this->initLayout();

    // 这个只是测试用的 还需要添加更多的控件
    this->resize(600, 400);
    this->setLayout(drawerLayout);
}

void InterfaceDisplay::initLayout()
{
    this->ecgDrawer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->ibp2Drawer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->spo2Drawer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->ecgDrawer->setLabelText("ECG");
    this->spo2Drawer->setLabelText("SPO2");
    this->ibp2Drawer->setLabelText("IBP2");

    // 创建垂直箱式 layout
    // 添加波形绘制到 layout 中
    this->drawerLayout = new QVBoxLayout();
    this->drawerLayout->addWidget(this->ecgDrawer);
    this->drawerLayout->addWidget(this->spo2Drawer);
    this->drawerLayout->addWidget(this->ibp2Drawer);
}

void InterfaceDisplay::closeEvent(QCloseEvent *event)
{
    emit closeWindow();
}
