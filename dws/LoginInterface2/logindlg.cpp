#include "logindlg.h"
#include "databasedata.h"
#include "ui_logindlg.h"
#include <QMessageBox>
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>





LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_LoginPButton_clicked()
{
    //连接数据库
    DatabaseData database;



    //判断用户名和密码是否正确
    //如果错误则弹出警告对话框
    //读取数据库的用户名和密码
    if(database.VerificationLogin(ui->UserNameEdit->text().trimmed(), ui->PasswordEdit->text().trimmed()))//trimmed表示修剪的，去掉编辑框前面的空格ui->UserNameEdit->text().trimmed() == "admin" && ui->PasswordEdit->text() == "nengxing"
    {
        //登录成功，则触发accept函数
        accept();
        QMessageBox::warning(this,tr("警告！"),tr("登录成功！"),QMessageBox::Yes);
// /////////
        // 查询 db参数指定连接
        QSqlQuery query(db);

//        query.exec("SELECT * FROM doctors");
        // 方法2
//        QString userid = "d1";
//        QString sql = "SELECT * FROM doctors WHERE uid='";
//        sql += userid;
//        sql += "'";
//        qDebug()<<sql;
//        query.exec(sql);
        // 方法三
        QString userid = "d1";
        query.prepare("SELECT * FROM doctors WHERE uid = :id");
        query.bindValue(":id", userid);
        query.exec();

        qDebug()<<query.size();
        while (query.next()) {
            qDebug()<<query.value("name")<<query.value("mobile");
            QString name = query.value("name").toString();
            QString mobile = query.value("mobile").toString();
            qDebug()<<name<<mobile;
        }

        //  工作站从数据库读取数据
        query.prepare("SELECT * FROM sample WHERE time > :start and time < :end");
        query.bindValue(":start", "2020-07-22 11:00:00");
        query.bindValue(":end", "2020-07-22 12:00:00");

        bool queryOk;
        queryOk = query.exec();
        if(queryOk)
        {
//            qDebug()<<query.size();
            while(query.next())
            {
//                QByteArray waveData = query.value("value").toByteArray();
                // todo, 画波形
//                qDebug()<<query.size()<<waveData;
                qDebug()<<"得到波形数据";
            }
        }else
        {
            qDebug()<<"读取错误"<<query.lastError();
        }
 /******************** 下午 *************/

/*
 * 以上代码在工作站
 ************************************************************
 * 下面代码运行在设备端
 */
        query.prepare("SELECT * from device "
                      "WHERE serial = :serial");
        query.bindValue(":serial", "DEV-007");

        int dev_id = 1;
        if(query.exec())
        {
            qDebug()<<"size"<<query.size();
            if(query.size() > 0)
            {
                query.next();
                qDebug()<<"设备已存在";
                dev_id = query.value("dev_id").toInt();
                qDebug()<<"当前设备编号："<<dev_id;
            }
            else
            {
                query.prepare("INSERT INTO device (serial)"
                              "VALUES (:serial)");
                query.bindValue(":serial", "DEV-007");
                if (!query.exec())
                {
                    qDebug("设备注册失败！");
                }
                else
                {
                    qDebug("设备注册成功！");
                }
            }
        }else
        {
            qDebug()<<"查看设备错误";
        }

        // 模拟终端设备，上传数据波形
        // 方法2 bindValue
        query.prepare("INSERT INTO sample (value, time, dev_id) VALUES (:array, :time, :dev_id)");
        // 与数据库中数据类型一致的十六进制数组
        short samples[3] = {2000,2001,2002};
        QByteArray waves2((char*)samples, sizeof(samples));

        query.bindValue(":array", waves2);
        // 绑定当前时间
        query.bindValue(":time", QDateTime::currentDateTime());
        // 绑定设备ID
        query.bindValue(":dev_id", dev_id);
        // 执行sql语句
        queryOk = query.exec();
        if (queryOk) qDebug()<<"写波形成功";
        else qDebug()<<"写波形错误："<<query.lastError();

        // 每15s更新一次refresh 字段 判定离线条件为refresh时间与当前时间差值超过20s
        query.prepare("UPDATE `medical_monitor1`.`device` SET refresh = NOW() WHERE dev_id = :dev_id");
        query.bindValue(":dev_id", 1);
        queryOk = query.exec();
        if(!queryOk)
            qDebug()<<"更新设备在线状态错误";









    }
    else
    {
        //登录失败，清空用户编辑框，密码编辑框，设置光标到用户编辑框
        QMessageBox::warning(this,tr("警告！"),tr("用户名或者密码错误！"),QMessageBox::Yes);
        ui->UserNameEdit->clear();//清空用户编辑框
        ui->PasswordEdit->clear();
        ui->UserNameEdit->setFocus();//设置光标到用户编辑框
    }
}
