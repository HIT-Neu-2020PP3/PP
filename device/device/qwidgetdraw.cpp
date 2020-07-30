#include "qwidgetdraw.h"


QWidgetDraw::QWidgetDraw(QWidget *parent) : QWidget(parent)
{
//    this->resize(1600, 300);
    this->label = new QLabel(this);
    this->label->setStyleSheet("color: white");

    this->map = QPixmap(this->width(), this->height());
    this->map.fill(Qt::black);

}

QWidgetDraw::QWidgetDraw(int cycle, int *wave, int waveLen, int maxData, QWidget *parent)
    :QWidget(parent),  waveLength(waveLen), wave(wave), maxData(maxData)
{
//    this->resize(1600, 400);
    this->label = new QLabel(this);
    this->label->setStyleSheet("color: white");

    this->map = QPixmap(this->width(), this->height());
    this->map.fill(Qt::black);

    this->timer = new QTimer(this);
    this-> timer->start(cycle);
    connect(timer, &QTimer::timeout, this, &QWidgetDraw::sendData);
    connect(this, &QWidgetDraw::rxDataSignal, this, &QWidgetDraw::refreshFromData);
}

void QWidgetDraw::setLabelText(const QString &s)
{
    this->label->setText(s);
}

void QWidgetDraw::sendData()
{
    int data = 0;
    int height = this->height();
    data = height - wave[index]*height/maxData;

    this->index += 1;

    if (this->index >= waveLength)
        this->index = 0;

    emit rxDataSignal(data);
}

void QWidgetDraw::refreshFromData(int data)
{
    QPainter *painter = new QPainter();
    painter->begin(&this->map);
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::green);
    painter->setPen(*pen);


    this->drawWave(painter, data);
    painter->end();
    // update 触发 paintEvent 事件
    this->update();
}

void QWidgetDraw::refresh()
{
    QPainter *painter = new QPainter();
    painter->begin(&this->map);

    this->draw(painter);

    painter->end();
    // update 触发 paintEvent 事件
    this->update();
}

// 什么触发了这个事件
void QWidgetDraw::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter();

    painter->begin(this);
//    this->draw(painter);
    painter->drawPixmap(0, 0, this->map);

    painter->end();
}

void QWidgetDraw::resizeEvent(QResizeEvent *event)
{
    QPixmap cleanmap = QPixmap(this->width(), this->height());
    cleanmap.fill(Qt::black);
    // 析构指针
    this->map = cleanmap;
    this->x = 0;
//    this->y = 0;
}

void QWidgetDraw::draw(QPainter *painter)
{
    QPen *pen = new QPen();
    pen->setWidth(2);
    pen->setColor(Qt::green);
    painter->setPen(*pen);

    this->drawWaveFromArray(painter);
}

void QWidgetDraw::drawTriangleNew(QPainter *painter)
{
    int width = this->width();
    int height = this->height();

    QPen *pen = new QPen();
    pen->setWidth(4);
    pen->setColor(Qt::black);
    // 保存原来参数
    painter->save();
    // 新的配置
    painter->setPen(*pen);

    // 擦除
    painter->drawLine(x, 0, x, height);
    // 还原配置
    painter->restore();

    painter->drawPoint(x, height-y);
    x += 1;

    if(0 == dir)
    {
        y += 1;
        if(y > height/2)
            dir = 1;
    }else
    {
        y -= 1;
        if(0 == y)
            dir = 0;
    }

    if(x >= width)
        x = 0;
}

void QWidgetDraw::drawTriangle(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int cnt;
    int x,y;
    int dir = 0;

    x = 0;
    y = 0;
    for(cnt = 0; cnt < width; cnt ++)
    {
        painter->drawPoint(x, height-y);
        x += 1;

        if(0 == dir)
        {
            y += 1;
            if(y > height/2)
                dir = 1;
        }else
        {
            y -= 1;
            if(0 == y)
                dir = 0;
        }
    }
}


void QWidgetDraw::drawWaveFromArray(QPainter *painter)
{
    int data = 0;
    int height = this->height();
    data = height - wave[index]*height/maxData;
    this->drawWave(painter, data);

    this->index += 3;

    if (this->index >= waveLength)
        this->index = 0;

}

void QWidgetDraw::drawWave(QPainter *painter, int data)
{
    int width = this->width();
    int height = this->height();

    QPen *pen = new QPen();
    pen->setWidth(4);
    pen->setColor(Qt::black);
    // 保存原来参数
    painter->save();
    // 新的配置
    painter->setPen(*pen);

    // 擦除
    painter->drawLine(this->x+2, 0, this->x+2, height);
    // 还原配置
    painter->restore();

//    painter->drawPoint(x, data);
    painter->drawLine(this->x-1, lastData, this->x, data);
    lastData = data;

    this->x += 1;

    if (this->x >= width)
        this->x = 0;
}
