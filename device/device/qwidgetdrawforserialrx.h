#ifndef QWIDGETDRAWFORSERIALRX_H
#define QWIDGETDRAWFORSERIALRX_H

#include "qwidgetdraw.h"

class QWidgetDrawForSerialRx : public QWidgetDraw
{
    Q_OBJECT
public:

    QWidgetDrawForSerialRx(int maxDa, const QColor &color = Qt::green, QWidget *parent = nullptr);

    int maxData;
    QColor waveColor;
    void refreshFromData(char pID, int data);
};

#endif // QWIDGETDRAWFORSERIALRX_H
