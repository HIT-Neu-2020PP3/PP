#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QTableView>
#include <QString>
#include <QQueue>
#include <QTimer>
#include "interfacedisplay.h"
#include "workingstationclient.h"
#include "qwidgetdrawforserialrx.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    bool btnc1=0;
    bool btnc2=0;
    bool btnc3=0;

    // 缓存器
    QQueue<int> ecgBuffer;
    QQueue<int> ibp2Buffer;
    QQueue<int> spo2Buffer;

    // 另一个缓存 用来做中间缓存位置、
    // 没那么多时间思考了 直接先做出一个版本来吧
    QByteArray ecgBuffer_A;
    QByteArray ibp2Buffer_A;
    QByteArray spo2Buffer_A;

    void putin(QTableView *view_in,QTableView *patientView_in,QTableView *devicePatientView_in );
    explicit Widget(quint16 port, QWidget *parent = 0);
    ~Widget();

    InterfaceDisplay *displayer;
    WorkingStationClient *wsClient;

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void processData(char pID, const QByteArray &ba);

    void getEcgData();
    void getIBP2Data();
    void getSPO2Data();

private:
    Ui::Widget *ui;
    QTableView *view;
    QTableView *patientView;
    QTableView *devicePatientView ;

    QTimer *refreshEcgTimer;
    QTimer *refreshIbp2Timer;
    QTimer *refreshSPO2Timer;

    int patient_id = 100;
    void drawwave();



signals:
    void rxEcgDataSignal(char pID, int data);
    void rxIbp2DataSignal(char pID, int data);
    void rxSpo2DataSignal(char pID, int data);
    void queryForData(int patient_id, char pID);




};

#endif // WIDGET_H
