#include "widget.h"
#include "ui_widget.h"
#include "databasedata.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

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
    QString lookfor_id=ui->lineEdit->text();
    qDebug()<<"查询对应的病人ID"<<lookfor_id;
    QSqlQuery query(db);


    query.prepare("SELECT dev_id from medical_monitor1.device_patient where id= :id") ;
    query.bindValue(":id",lookfor_id.toInt());
    query.exec();   //查询病人所对应的设备号
    qDebug()<<query.lastError();
    query.first();
    QString lookfor_device_id=query.value("dev_id").toString();
    qDebug()<<"查询对应的设备号"<<lookfor_device_id;

    query.prepare("SELECT value from sample where dev_id= :id2") ;
    query.bindValue(":id2",lookfor_device_id);
    query.exec();   //查询对应设备的采样值
    bool queryOk;
    queryOk = query.exec();
    if(queryOk&&query.size()>0)
    {
        qDebug()<<query.size();
        while(query.next())
        {
            QByteArray waveData = query.value("value").toByteArray();
            // todo, 画波形
            qDebug()<<query.size()<<waveData;

            qDebug()<<"得到波形数据";
        }
          drawwave();
    }else
    {
        qDebug()<<"读取错误"<<query.lastError();
        QMessageBox::warning(this,tr("提示！"),tr("未查到此病人相关数据"),QMessageBox::Yes);
        ui->lineEdit->clear();
    }

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

