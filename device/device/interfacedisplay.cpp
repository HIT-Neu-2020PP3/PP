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

    this->initMainLayout();
    this->setStyleSheet("background: rgb(0, 0, 0)");
    // 这个只是测试用的 还需要添加更多的控件
    this->resize(600, 400);
    this->setLayout(this->mainLayout);
}



//主layout
void InterfaceDisplay::initMainLayout()
{
    this->initUpLayout();
    this->initDownLayout();
    // 初始化主 layout
    this->mainLayout = new QVBoxLayout();
    this->mainLayout->addLayout(this->upLayout);
    this->mainLayout->addLayout(this->downLayout);
    // 配置拉伸因子
    this->mainLayout->setStretchFactor(this->upLayout, 1);
    this->mainLayout->setStretchFactor(this->downLayout, 10);
}
//下边栏layout
void InterfaceDisplay::initDownLayout()
{
    this->initDrawerLayout();
    this->initRightSideWidgetLayout();
    // 初始化主 layout
    this->downLayout = new QHBoxLayout();

    this->downLayout->addLayout(this->drawerLayout);
    this->downLayout->addLayout(this->rightSideWidgetLayout);
    // 配置拉伸因子
    this->downLayout->setStretchFactor(this->drawerLayout, 2);
    this->downLayout->setStretchFactor(this->rightSideWidgetLayout, 1);
}

//右边layout
void InterfaceDisplay::initRightSideWidgetLayout()
{
    this->oneLayout();
    this->twoLayout();
    this->threeLayout();
    this->fourLayout();

    this->rightSideWidgetLayout = new QVBoxLayout();
    rightSideWidgetLayout->setMargin(0);
    rightSideWidgetLayout->setSpacing(2);
    this->rightSideWidgetLayout->addLayout(this->ONELayout);
    this->rightSideWidgetLayout->addLayout(this->TWOLayout);
    this->rightSideWidgetLayout->addLayout(this->THREELayout);
    this->rightSideWidgetLayout->addLayout(this->FOURLayout);


}
// 初始化画图部分的 layout
void InterfaceDisplay::initDrawerLayout()
{
    this->ecgDrawer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->ibp2Drawer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->spo2Drawer->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->ecgDrawer->setLabelText("ECG         ×1");
    this->spo2Drawer->setLabelText("SPO2        ×1");
    this->ibp2Drawer->setLabelText("IBP2        ×1");

    this->ecgDrawer->setStyleSheet("color:red;");

    // 创建垂直箱式 layout
    // 添加波形绘制到 layout 中
    this->drawerLayout = new QVBoxLayout();
    this->drawerLayout->addWidget(this->ecgDrawer);
    this->drawerLayout->addWidget(this->spo2Drawer);
    this->drawerLayout->addWidget(this->ibp2Drawer);
}


void InterfaceDisplay::oneLayout()
{
    this->oneLeftLayout();
    this->oneRightLayout();
    // 初始化主 layout
    this->ONELayout = new QHBoxLayout();
    this->ONELayout->addLayout(this->ONEleftLayout);
    this->ONELayout->addLayout(this->ONErightLayout);
    ONELayout->setSpacing(2);
    // 配置拉伸因子
    //this->ONELayout->setStretchFactor(this->ONEleftLayout, 1);
    //this->ONELayout->setStretchFactor(this->ONEleftLayout, 5);
}

//右边第一行左
void InterfaceDisplay::oneLeftLayout()
{
    this->ONEleftLayout = new  QVBoxLayout();

    this->titleLeftOne = new QLabel("HR");
    this->charLeftOne = new QLabel("bpm");
    this->dataLeftOne = new QLabel("80");

    titleLeftOne->setStyleSheet("QLabel{color:rgb(210, 210, 210); font: 10pt , SimHei; background: rgb(50, 50, 50);}");
    charLeftOne->setStyleSheet("QLabel{color:rgb(0, 255, 0); font: 10pt , SimHei; background: rgb(10, 10, 10);}");
    dataLeftOne->setStyleSheet("QLabel{color:rgb(0, 255, 0); font: 30pt , SimHei; background: rgb(10, 10, 10);}");

    this->titleLeftOne->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charLeftOne->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataLeftOne->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->ONEleftLayout->addWidget(titleLeftOne);
    this->ONEleftLayout->addWidget(charLeftOne, 0, Qt::AlignRight);
    this->ONEleftLayout->addWidget(dataLeftOne, 0, Qt::AlignCenter);

    this->ONEleftLayout->setStretchFactor(this->titleLeftOne, 1);
    this->ONEleftLayout->setStretchFactor(this->charLeftOne, 1);
    this->ONEleftLayout->setStretchFactor(this->dataLeftOne, 4);
}
//右边第一行右
void InterfaceDisplay::oneRightLayout()
{
    this->ONErightLayout = new  QVBoxLayout();

    this->titleRightOne = new QLabel("ST");
    this->charRightOneA = new QLabel("st1 -?-");
    this->charRightOneB = new QLabel("st1 -?-");
    this->dataRightOne = new QLabel("PVCs -?-");

    titleRightOne->setStyleSheet("QLabel{color:rgb(210, 210, 210); font: 10pt , SimHei; background: rgb(50, 50, 50);}");
    charRightOneA->setStyleSheet("QLabel{color:rgb(0, 255, 0); font: 15pt , SimHei; background: rgb(10, 10, 10);}");
    charRightOneB->setStyleSheet("QLabel{color:rgb(0, 255, 0); font: 15pt , SimHei; background: rgb(10, 10, 10);}");
    dataRightOne->setStyleSheet("QLabel{color:rgb(0, 255, 0); font: 15pt , SimHei; background: rgb(10, 10, 10);}");

    this->titleRightOne->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charRightOneA->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charRightOneB->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataRightOne->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->ONErightLayout->addWidget(titleRightOne);
    this->ONErightLayout->addWidget(charRightOneA, 0, Qt::AlignCenter);
    this->ONErightLayout->addWidget(charRightOneB, 0, Qt::AlignCenter);
    this->ONErightLayout->addWidget(dataRightOne, 0, Qt::AlignCenter);

    this->ONErightLayout->setStretchFactor(this->titleRightOne, 1);
    this->ONErightLayout->setStretchFactor(this->charRightOneA, 1);
    this->ONErightLayout->setStretchFactor(this->charRightOneB, 1);
    this->ONErightLayout->setStretchFactor(this->dataRightOne, 2);
}

//右边第二行
void InterfaceDisplay::twoLayout()
{
    this->TWOLayout = new  QVBoxLayout();

    this->titleTwo = new QLabel("NIBP");
    this->charTwo = new QLabel("mmHg");
    this->dataTwo = new QLabel("-?- / -?-");

    titleTwo->setStyleSheet("QLabel{color:rgb(210, 210, 210); font: 10pt , SimHei; background: rgb(50, 50, 50);}");
    charTwo->setStyleSheet("QLabel{color:rgb(0, 255, 255); font: 10pt , SimHei; background: rgb(10, 10, 10);}");
    dataTwo->setStyleSheet("QLabel{color:rgb(0, 255, 255); font: 40pt , SimHei; background: rgb(10, 10, 10);}");

    this->titleTwo->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charTwo->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataTwo->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->TWOLayout->addWidget(titleTwo);
    this->TWOLayout->addWidget(charTwo, 0, Qt::AlignRight);
    this->TWOLayout->addWidget(dataTwo, 0, Qt::AlignCenter);

    this->TWOLayout->setStretchFactor(this->charTwo, 1);
    this->TWOLayout->setStretchFactor(this->charTwo, 1);
    this->TWOLayout->setStretchFactor(this->dataTwo, 4);
}

//右边第三行
void InterfaceDisplay::threeLayout()
{
    this->threeLeftLayout();
    this->threeRightLayout();
    // 初始化主 layout
    this->THREELayout = new QHBoxLayout();
    THREELayout->setSpacing(2);
    this->THREELayout->addLayout(this->THREEleftLayout);
    this->THREELayout->addLayout(this->THREErightLayout);
    // 配置拉伸因子
    //this->THREELayout->setStretchFactor(this->upLayout, 1);
    //this->THREELayout->setStretchFactor(this->downLayout, 5);
}

//右边第三行左
void InterfaceDisplay::threeLeftLayout()
{
    this->THREEleftLayout = new  QVBoxLayout();

    this->titleLeftThree = new QLabel("SpO2");
    this->charLeftThree = new QLabel("%");
    this->dataLeftThree = new QLabel(" 98");

    titleLeftThree->setStyleSheet("QLabel{color:rgb(210, 210, 210); font: 10pt , SimHei; background: rgb(50, 50, 50);}");
    charLeftThree->setStyleSheet("QLabel{color:rgb(255, 0, 0); font: 10pt , SimHei; background: rgb(10, 10, 10);}");
    dataLeftThree->setStyleSheet("QLabel{color:rgb(255, 0, 0); font: 30pt , SimHei; background: rgb(10, 10, 10);}");

    this->titleLeftThree->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charLeftThree->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataLeftThree->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->THREEleftLayout->addWidget(titleLeftThree);
    this->THREEleftLayout->addWidget(charLeftThree, 0, Qt::AlignRight);
    this->THREEleftLayout->addWidget(dataLeftThree, 0, Qt::AlignCenter);

    this->THREEleftLayout->setStretchFactor(titleLeftThree, 1);
    this->THREEleftLayout->setStretchFactor(charLeftThree, 1);
    this->THREEleftLayout->setStretchFactor(dataLeftThree, 4);
}
//右边第三行右
void InterfaceDisplay::threeRightLayout()
{
    this->THREErightLayout = new  QVBoxLayout();

    this->titleRightThree = new QLabel("TEMP");
    this->charRightThree = new QLabel("℃");
    this->dataRightThreeA = new QLabel("T1 -?-");
    this->dataRightThreeB = new QLabel("T2 -?-");

    titleRightThree->setStyleSheet("QLabel{color:rgb(210, 210, 210); font: 10pt , SimHei; background: rgb(50, 50, 50);}");
    charRightThree->setStyleSheet("QLabel{color:rgb(255, 0, 0); font: 10pt , SimHei; background: rgb(10, 10, 10);}");
    dataRightThreeA->setStyleSheet("QLabel{color:rgb(255,0,0); font: 20pt , SimHei; background: rgb(10, 10, 10);}");
    dataRightThreeB->setStyleSheet("QLabel{color:rgb(255,0,0); font: 20pt , SimHei; background: rgb(10, 10, 10);}");

    this->titleRightThree->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charRightThree->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataRightThreeA->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataRightThreeB->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->THREErightLayout->addWidget(titleRightThree);
    this->THREErightLayout->addWidget(charRightThree, 0, Qt::AlignRight);
    this->THREErightLayout->addWidget(dataRightThreeA, 0, Qt::AlignCenter);
    this->THREErightLayout->addWidget(dataRightThreeB, 0, Qt::AlignCenter);

    this->THREErightLayout->setStretchFactor(titleRightThree, 1);
    this->THREErightLayout->setStretchFactor(charRightThree, 1);
    this->THREErightLayout->setStretchFactor(dataRightThreeA, 2);
    this->THREErightLayout->setStretchFactor(dataRightThreeB, 2);
}

//右边第四行
void InterfaceDisplay::fourLayout()
{
    this->fourLeftLayout();
    this->fourRightLayout();
    // 初始化主 layout
    this->FOURLayout = new QHBoxLayout();
    FOURLayout->setSpacing(2);
    this->FOURLayout->addLayout(this->FOURleftLayout);
    this->FOURLayout->addLayout(this->FOURrightLayout);
    // 配置拉伸因子
    //this->mainLayout->setStretchFactor(this->upLayout, 1);
    //this->mainLayout->setStretchFactor(this->downLayout, 5);
}

//右边第四行左
void InterfaceDisplay::fourLeftLayout()
{
    this->FOURleftLayout = new  QVBoxLayout();

    this->titleLeftFour = new QLabel("RESP");
    this->charLeftFour = new QLabel("bpm");
    this->dataLeftFour = new QLabel(" -?-");

    titleLeftFour->setStyleSheet("QLabel{ color:rgb(210, 210, 210); font: 10pt , SimHei; background: rgb(50, 50, 50);}");
    charLeftFour->setStyleSheet("QLabel{color:rgb(255, 255,0); font: 10pt , SimHei; background: rgb(10, 10, 10);}");
    dataLeftFour->setStyleSheet("QLabel{color:rgb(255, 255, 0); font: 30pt , SimHei; background: rgb(10, 10, 10);}");

    this->titleLeftFour->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charLeftFour->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataLeftFour->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->FOURleftLayout->addWidget(titleLeftFour);
    this->FOURleftLayout->addWidget(charLeftFour, 0, Qt::AlignRight);
    this->FOURleftLayout->addWidget(dataLeftFour, 0, Qt::AlignCenter);

    this->FOURleftLayout->setStretchFactor(titleLeftFour, 1);
    this->FOURleftLayout->setStretchFactor(charLeftFour, 1);
    this->FOURleftLayout->setStretchFactor(dataLeftFour, 4);
}
//右边第四行右
void InterfaceDisplay::fourRightLayout()
{
    this->FOURrightLayout = new  QVBoxLayout();

    this->titleRightFour = new QLabel("CO2");
    this->charRightFour = new QLabel("mmHg");
    this->dataRightFour = new QLabel(" -?-");

    titleRightFour->setStyleSheet("QLabel{color:rgb(210, 210, 210); font: 10pt , SimHei; background: rgb(50, 50, 50);}");
    charRightFour->setStyleSheet("QLabel{color:rgb(255, 255, 0); font: 10pt , SimHei; background: rgb(10, 10, 10);}");
    dataRightFour->setStyleSheet("QLabel{color:rgb(255, 255, 0); font: 30pt , SimHei; background: rgb(10, 10, 10);}");

    this->titleRightFour->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->charRightFour->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->dataRightFour->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->FOURrightLayout->addWidget(titleRightFour);
    this->FOURrightLayout->addWidget(charRightFour, 0, Qt::AlignRight);
    this->FOURrightLayout->addWidget(dataRightFour, 0, Qt::AlignCenter);

    this->FOURrightLayout->setStretchFactor(titleRightFour, 1);
    this->FOURrightLayout->setStretchFactor(charRightFour, 1);
    this->FOURrightLayout->setStretchFactor(dataRightFour, 4);
}


//上边layout
void InterfaceDisplay::initUpLayout()
{
    this->upLayout = new  QHBoxLayout();

    this->btnA = new QLabel("ID:0011");
    this->btnB = new QLabel("云监护仪");
    this->btnC = new QLabel("name：Ernest");

    btnA->setStyleSheet("QLabel{text-align: left; color:rgb(210,210,210); font: 10pt , SimHei; background: rgb(0, 0, 0);}");
    btnB->setStyleSheet("QLabel{color:rgb(210,210,210); font: 20pt ;font-family: LiSu; background: rgb(0, 0, 0);}");
    btnC->setStyleSheet("QLabel{text-align: left; color:rgb(210,210,210); font: 10pt , SimHei; background: rgb(0, 0, 0);}");
    //btnA->setStyleSheet("color:rgb(255, 255, 255);font: 10pt , SimHei;");

    this->btnA->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->btnB->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
    this->btnC->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);

    this->upLayout->addWidget(btnA);
    this->upLayout->addWidget(btnB, 0, Qt::AlignCenter);
    this->upLayout->addWidget(btnC);

    this->upLayout->setStretchFactor(this->btnA, 1);
    this->upLayout->setStretchFactor(this->btnB, 3);
    this->upLayout->setStretchFactor(this->btnC, 1);

}


//layoutnew
