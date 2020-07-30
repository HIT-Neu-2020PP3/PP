#ifndef QWIDGETDRAW_H
#define QWIDGETDRAW_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QLabel>

class QWidgetDraw : public QWidget
{
    Q_OBJECT
public:
    QTimer *timer;
    QPixmap map;
    QLabel *label;
    int x = 0;
    int y = 0;
    int dir = 0;
    int cnt = 0;
    int index = 0;
    int lastData = 0;
    int waveLength = 0;
    int *wave;
    int maxData;

    QWidgetDraw(QWidget *parent = nullptr);
    QWidgetDraw(int cycle, int *wave, int waveLen, int maxData, QWidget *parent = nullptr);
    void draw(QPainter *painter);
    void drawDemo(QPainter *painter);
    void drawTriangle(QPainter *painter);
    void drawTriangleNew(QPainter *painter);
    void drawWaveFromArray(QPainter *painter);
    void drawWave(QPainter *painter, int data);
    void refresh();
    void refreshFromData(int data);
    void sendData();
    void setLabelText(const QString &s);
private:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
signals:
    void rxDataSignal(int data);

};

#endif // QWIDGETDRAW_H
