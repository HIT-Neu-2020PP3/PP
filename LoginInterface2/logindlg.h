#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include <databasedata.h>
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
            qDebug()<<"更新性别"<<value.toString();
            ok = this->setGender(id, value.toString());
        } else
        {
            qDebug()<<"error";
        }

        if (ok) this->setQuery("SELECT * FROM patients");
    }
};



namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

private slots:
    void on_LoginPButton_clicked();

private:
    Ui::LoginDlg *ui;
};

#endif // LOGINDLG_H
