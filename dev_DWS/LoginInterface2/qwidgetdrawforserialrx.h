#ifndef QWIDGETDRAWFORSERIALRX_H
#define QWIDGETDRAWFORSERIALRX_H

#include "qwidgetdraw.h"

class QWidgetDrawForSerialRx : public QWidgetDraw
{
    Q_OBJECT
public:

    QWidgetDrawForSerialRx(int maxDa, QWidget *parent = nullptr);

    int maxData;
    void refreshFromData(char pID, int data);
};

#endif // QWIDGETDRAWFORSERIALRX_H
