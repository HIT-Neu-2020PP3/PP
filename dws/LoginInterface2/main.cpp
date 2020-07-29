#include "widget.h"
#include <QApplication>
#include "logindlg.h"
#include <QDebug>

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include "databasedata.h"






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    LoginDlg dlg;//建立自己新建的LoginDlg类的实例Dlg
    if(dlg.exec() == QDialog::Accepted)
    {
        w.show();//如果被按下，显示窗口

        /*
        * 下面代码运行在工作站
        */
            // 显示设备列表
            // 创建表格对象
            QWidget *mainWin  = new QWidget();
            // 显示设备列表
            // 创建表格对象
            QTableView *view = new QTableView();

            // 创建模型对象
            QSqlQueryModel model;
            model.setQuery("SELECT dev_id, serial, now()-refresh < 20 AS online FROM device");

            view->setModel(&model);
            view->show();

            // 显示病人列表
            // 创建表格对象
            QTableView *patientView = new QTableView();

            // 创建模型对象
            PatientModel patientModel;
        //    patientModel.setQuery("SELECT * FROM patients");

            patientView->setModel(&patientModel);
            patientView->show();

            QTableView *devicePatientView = new QTableView();

            // 创建模型对象
            QSqlQueryModel devicePatientModel;
            devicePatientModel.setQuery("SELECT * FROM patients "
                           "LEFT JOIN device_patient "
                           "ON patients.id = device_patient.id "
                           "LEFT JOIN device "
                           "ON device.dev_id = device_patient.dev_id");

            devicePatientView->setModel(&devicePatientModel);
            devicePatientView->show();










        return a.exec();//程序一直执行，直到主窗口关闭
    }
    else return 0;//如果没有被按下，则不会进入主窗口，整个程序结束运行
}
