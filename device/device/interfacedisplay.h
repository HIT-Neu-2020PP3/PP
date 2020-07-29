#ifndef INTERFACEDISPLAY_H
#define INTERFACEDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "qwidgetdraw.h"
#include "qwidgetdrawforserialrx.h"

/*
 * 获得从串口而来的数据进行绘图
 *
 * 这边里面具体的函数没有写了 有不明白的再说吧
 *
*/

class InterfaceDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit InterfaceDisplay(QWidget *parent = nullptr);

    InterfaceDisplay(int maxE, int maxS, int maxI, QWidget *parent = nullptr);

    // 主 layout 设置 调用其他 layout 的设置 并把其他 layout 添加到主 layout 中
    void initMainLayout();
    //最终 layout
    void initLayout();
    // 波形部分的 layout 设置
    void initDrawerLayout();
    // 右边 layout 设置
    void initRightSideWidgetLayout();
    //右边第一行
    void oneLayout();
    void oneLeftLayout();
    void oneRightLayout();
    //右边第二行
    void twoLayout();
    //右边第三行
    void threeLayout();
    void threeLeftLayout();
    void threeRightLayout();
    //右边第四行
    void fourLayout();
    void fourLeftLayout();
    void fourRightLayout();
    //上边layout
    void initUpLayout();
    //下边layout
    void initDownLayout();



    // 接收绘图部分来的信号进行绘图
    // 也许可以只用一个 但是建立三个也许并无大碍
    QWidgetDrawForSerialRx *ecgDrawer;
    QWidgetDrawForSerialRx *spo2Drawer;
    QWidgetDrawForSerialRx *ibp2Drawer;

    // 画图所需要的最大值
    int maxEcg;
    int maxSPO2;
    int maxIBP2;

    // mainLayout
    QVBoxLayout *mainLayout;
    // 波形部分的 layout 布局
    QVBoxLayout *drawerLayout;
    // 右边控件的 layout 布局 (这里只考虑了波形和其他控件左右布局)
    QVBoxLayout *rightSideWidgetLayout;
    // 下边栏Layout
    QHBoxLayout *downLayout;
    // 上边控件 layout
    QHBoxLayout *upLayout;
    //右边各行
    QHBoxLayout *ONELayout;
    QVBoxLayout *ONEleftLayout;
    QVBoxLayout *ONErightLayout;

    QVBoxLayout *TWOLayout;

    QHBoxLayout *THREELayout;
    QVBoxLayout *THREEleftLayout;
    QVBoxLayout *THREErightLayout;

    QHBoxLayout *FOURLayout;
    QVBoxLayout *FOURleftLayout;
    QVBoxLayout *FOURrightLayout;


/*
 * 这里需要添加其他一些控件 才能实现最终的目标
 * 此外还需要其他的一些调整
 *
 * 这就是需要插入控件的地方 应该还需要许多控件 你们自己把握
*/
    //QLabel *widgetHr;
    //QLabel *widgetNibp;

    //右边栏按钮
    QLabel *titleLeftOne;
    QLabel *charLeftOne;
    QLabel *dataLeftOne;

    QLabel *titleRightOne;
    QLabel *charRightOneA;
    QLabel *charRightOneB;
    QLabel *dataRightOne;

    QLabel *titleTwo;
    QLabel *charTwo;
    QLabel *dataTwo;

    QLabel *titleLeftThree;
    QLabel *charLeftThree;
    QLabel *dataLeftThree;

    QLabel *titleRightThree;
    QLabel *charRightThree;
    QLabel *dataRightThreeA;
    QLabel *dataRightThreeB;

    QLabel *titleLeftFour;
    QLabel *charLeftFour;
    QLabel *dataLeftFour;

    QLabel *titleRightFour;
    QLabel *charRightFour;
    QLabel *dataRightFour;



    //上边栏按钮
    QLabel *btnA;
    QLabel *btnB;
    QLabel *btnC;

signals:

};

#endif // INTERFACEDISPLAY_H
