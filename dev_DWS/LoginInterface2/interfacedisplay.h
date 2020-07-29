#ifndef INTERFACEDISPLAY_H
#define INTERFACEDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
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

    void initLayout();

    void closeEvent(QCloseEvent *event);
    // 接收绘图部分来的信号进行绘图
    // 也许可以只用一个 但是建立三个也许并无大碍
    QWidgetDrawForSerialRx *ecgDrawer;
    QWidgetDrawForSerialRx *spo2Drawer;
    QWidgetDrawForSerialRx *ibp2Drawer;

    // 画图所需要的最大值
    int maxEcg;
    int maxSPO2;
    int maxIBP2;

    // layout 布局
    QVBoxLayout *drawerLayout;

/*
 * 这里需要添加其他一些控件 才能实现最终的目标
 * 此外还需要其他的一些调整
 */

signals:
    void closeWindow();

};

#endif // INTERFACEDISPLAY_H
