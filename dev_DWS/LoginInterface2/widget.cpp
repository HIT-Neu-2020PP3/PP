#include "widget.h"
#include "ui_widget.h"
#include "databasedata.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QPainter>

Widget::Widget(quint16 port, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    int i = 0;
    for (; i < 10; i++) {
        this->ecgBuffer.append(100);
        this->ibp2Buffer.append(100);
        this->spo2Buffer.append(100);
    }


    this->displayer = new InterfaceDisplay(4096, 100, 80);
    this->wsClient = new WorkingStationClient(port);

    this->refreshEcgTimer = new QTimer();
    this->refreshIbp2Timer = new QTimer();
    this->refreshSPO2Timer = new QTimer();

    connect(this->wsClient, &WorkingStationClient::processRxDataSignal, this, &Widget::processData);
    connect(this, &Widget::queryForData, this->wsClient, &WorkingStationClient::queryRequest);


    connect(this, &Widget::rxEcgDataSignal, this->displayer->ecgDrawer, &QWidgetDrawForSerialRx::refreshFromData);
    connect(this, &Widget::rxSpo2DataSignal, this->displayer->spo2Drawer, &QWidgetDrawForSerialRx::refreshFromData);
    connect(this, &Widget::rxIbp2DataSignal, this->displayer->ibp2Drawer, &QWidgetDrawForSerialRx::refreshFromData);

    connect(this->refreshEcgTimer, &QTimer::timeout, this, &Widget::getEcgData);
    connect(this->refreshIbp2Timer, &QTimer::timeout, this, &Widget::getIBP2Data);
    connect(this->refreshSPO2Timer, &QTimer::timeout, this, &Widget::getSPO2Data);

    connect(this->displayer, &InterfaceDisplay::closeWindow, this->refreshEcgTimer, &QTimer::stop);
    connect(this->displayer, &InterfaceDisplay::closeWindow, this->refreshIbp2Timer, &QTimer::stop);
    connect(this->displayer, &InterfaceDisplay::closeWindow, this->refreshSPO2Timer, &QTimer::stop);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::putin(QTableView *view_in,QTableView *patientView_in,QTableView *devicePatientView_in )
{
    view=view_in;
    patientView=patientView_in;
    devicePatientView=devicePatientView_in;
}

void Widget::on_pushButton_2_clicked()
{
    patientView->show();
    btnc2=1;
    qDebug()<<btnc2;
}

void Widget::on_pushButton_3_clicked()
{
    devicePatientView->show();
    btnc3=1;
}

void Widget::on_pushButton_clicked()
{
    view->show();
    btnc1=1;
}

void Widget::on_pushButton_4_clicked()
{
    // 读取待查询的病人编号
    int patient_ID = ui->lineEdit->text().trimmed().toInt();
    qDebug()<<"patient_ID: "<<patient_ID;
    this->patient_id = patient_ID;

    this->refreshEcgTimer->start(2);
    this->refreshIbp2Timer->start(8);
    this->refreshSPO2Timer->start(4);


    qDebug()<<"启动所有信号连接";
    this->displayer->show();
    ui->lineEdit->clear();
}

void Widget::processData(char pID, const QByteArray &ba)
{
    if ( pID == 0x00 ) {
        qDebug()<<"接收信息错误";
         QMessageBox::warning(this,tr("提示！"),tr("未查到此病人相关数据"),QMessageBox::Yes);
        return;
    } else if ( pID == 0x08 ) {
        this->ecgBuffer_A = ba;
    } else if ( pID == 0x09 ) {
        this->spo2Buffer_A = ba;
    } else if ( pID == 0x0a ) {
        this->ibp2Buffer_A = ba;
    }
    qDebug()<<"信息已经更新";
}
void Widget::drawwave()//预计绘制心电波形（未完成）
{

    int ecgWave[]={2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2008, 2016, 2016, 2016, 2024, 2032, 2048,
                   2064, 2064, 2064, 2072, 2080, 2080, 2080, 2088, 2096, 2104,
                   2112, 2112, 2112, 2112, 2112, 2112, 2104, 2096, 2088,
                   2080, 2080, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2032,
                   2032, 2016, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 1992, 1984, 1976,
                   1968, 1960, 1952, 1944, 1936, 1944, 1952, 2016, 2080, 2136,
                   2192, 2256, 2320, 2376, 2432, 2488, 2544, 2568, 2592, 2536,
                   2480, 2424, 2368, 2304, 2240, 2184, 2128, 2072, 2016, 1968,
                   1920, 1928, 1936, 1944, 1952, 1960, 1968, 1984, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2008, 2016, 2024, 2032, 2032,
                   2032, 2048, 2064, 2064, 2064, 2072, 2080, 2088, 2096, 2104,
                   2112, 2112, 2112, 2120, 2128, 2136, 2144, 2152, 2160, 2160,
                   2160, 2160, 2160, 2168, 2176, 2176, 2176, 2184, 2192,
                   2192, 2192, 2192, 2200, 2208, 2208, 2208, 2208, 2208, 2208,
                   2208, 2200, 2192, 2192, 2192, 2184, 2176, 2176, 2176, 2168,
                   2160, 2160, 2160, 2144, 2128, 2128, 2128, 2128, 2128, 2112,
                   2096, 2088, 2080, 2072, 2064, 2064, 2064, 2048, 2032, 2024,
                   2016, 2016, 2016, 2008, 2000, 2000, 2000, 2000, 2000,
                   2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000
                  };
    QWidget *dr=new QWidget;
    dr->setWindowTitle("病人心电波形");

    int lastdata=0;
    int x = 0;
    unsigned int index=0;

    QPixmap *map=new QPixmap(dr->width(), dr->height());

    dr->resize(600,600);
    map->fill(Qt::black);



    QPainter *painter = new QPainter(dr);
    painter->begin(map);
    painter->end();


    QPen *pen = new QPen();
    pen->setWidth(4);
    pen->setColor(Qt::blue);
    painter->setPen(*pen);


    int width = dr->width();
    int height = dr->height();
    //创建画笔
    QPen *pen1 = new QPen();
    //参数配置
    pen1->setWidth(6);
    pen1->setColor(Qt::black);
    //保持配置
    painter->save();
    //新的配置
    painter->setPen(*pen);
    //背景擦除
    painter->drawLine(x+2,0,x+2,height);
    //还原配置
    //painter->restore();

    painter->drawLine(x-1,lastdata+100,x,height+100-ecgWave[index]*height/4096);
    painter->drawLine(x-1,lastdata-300,x,height-300-ecgWave[index]*height/4096);
    x+=1;
    lastdata=height-ecgWave[index]*height/4096;
    index+=4;

    if(index>=sizeof(ecgWave)/sizeof(int))
        index=0;
    if(x>=width)
        x=0;
        dr->show();    
}

void Widget::getEcgData()
{
    if ( this->ecgBuffer_A.isEmpty() ) {
        emit queryForData(this->patient_id, 0x08);
        return;
    }
    qDebug()<<"get ECG data";
    unsigned char high = this->ecgBuffer_A.at(0);
    unsigned char low = this->ecgBuffer_A.at(1);
    this->ecgBuffer_A.remove(0, 2); //移除
    int data = high;
    data = data << 8;
    data += low;
    this->ecgBuffer.enqueue(data);
    data = this->ecgBuffer.dequeue();
    emit rxEcgDataSignal(0x08, data);
}

void Widget::getIBP2Data()
{
    if ( this->ibp2Buffer_A.isEmpty() ) {
        emit queryForData(this->patient_id, 0x0a);
        return;
    }
    qDebug()<<"get IBP2 data";
    unsigned high = this->ibp2Buffer_A.at(0);
    int data = high;
    this->ibp2Buffer_A.remove(0, 1);    // 移除这个数据
    this->ibp2Buffer.enqueue(data);
    data = this->ibp2Buffer.dequeue();
    emit rxIbp2DataSignal(0x0a, data);
}

void Widget::getSPO2Data()
{
    if ( this->spo2Buffer_A.isEmpty() ) {
        emit queryForData(this->patient_id, 0x09);
        return;
    }
    qDebug()<<"get SPO2 data";
    unsigned high = this->spo2Buffer_A.at(0);
    int data = high;
    this->spo2Buffer_A.remove(0, 1);
    this->spo2Buffer.enqueue(data);
    data = this->spo2Buffer.dequeue();
    emit rxSpo2DataSignal(0x09, data);
}
