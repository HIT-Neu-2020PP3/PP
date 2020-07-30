#include "qwidgetdrawforserialrx.h"

QWidgetDrawForSerialRx::
QWidgetDrawForSerialRx(int maxD, const QColor &color, QWidget *parent)
    : QWidgetDraw(parent), waveColor(color), maxData(maxD)
{

}

void QWidgetDrawForSerialRx::
refreshFromData(char pID, int data)
{
    int height = this->height();
    data = height - data*height/this->maxData;

    QPainter *painter = new QPainter();
    painter->begin(&this->map);
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(this->waveColor);
    painter->setPen(*pen);


    this->drawWave(painter, data);
    painter->end();
    // update 触发 paintEvent 事件
    this->update();
}
