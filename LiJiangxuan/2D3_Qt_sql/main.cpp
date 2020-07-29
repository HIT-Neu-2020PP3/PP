#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

class PatientModel: public QSqlQueryModel
{
public:
    PatientModel()
    {
        this->setQuery("SELECT *FROM patients");
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
//        qDebug()<<"i am here"<<index.row()<<index.column();
        Qt::ItemFlags flags = QSqlQueryModel::flags(index);
        if (index.column() == 1 || index.column() == 2)
            flags |= Qt::ItemIsEditable;
        return flags;
    }

    bool setName(int id, const QString &name)
    {
        QSqlQuery query;

         query.prepare("UPDATE patients SET name = ? WHERE  id = ?");
         query.addBindValue(name);
         query.addBindValue(id);
         return query.exec();
    }

    bool setGender(int id, const QString &gender)
    {
        QSqlQuery query;

        query.prepare("UPDATE patients SET gender = ? WHERE  id = ?");
        query.addBindValue(gender);
        query.addBindValue(id);
        return query.exec();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int) override
    {
        if (index.column() < 1 || index.column() > 2)
            return false;
        // 获取当前列 当前行 用 sql 更新数据
        //
        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
        // 得到第 0 列的内容
        int id = this->data(primaryKeyIndex).toInt();

        bool ok = false;
        if (index.column() == 1)
        {
            //todo 更新姓名
            qDebug()<<"更新姓名"<<value.toString();
            ok = this->setName(id, value.toString());
        } else if (index.column() == 2)
        {
            //todo 更新性别
            qDebug()<<"更新性别";
            ok = this->setGender(id, value.toString());
        } else
        {
            qDebug()<<"error";
        }

        if (ok) this->setQuery("SELECT * FROM patients");
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // 服务器地址 本地 远程 IP 或者 域名
    db.setHostName("localhost");
    // 数据库名
    db.setDatabaseName("medical_monitor1");
    // 用户名及密码
    db.setUserName("doctor3");
    db.setPassword("1234567");
    bool openOK = db.open();

    if (openOK)
        qDebug()<<"OK";
    else
        qDebug()<<"BAD";

    if (openOK)
    {
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
        query.prepare("INSERT INTO ecg (value, time, dev_id) VALUES (:array, :time, :dev_id)");
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


    return a.exec();
}
