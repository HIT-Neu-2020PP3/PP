#ifndef DATABASEDATA_H
#define DATABASEDATA_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

extern QSqlDatabase db;

class DatabaseData
{
public:
    DatabaseData();

    //返回值为true表示打开成功，返回值为false表示打开失败
    bool VerificationLogin(QString Username, QString Password);//验证登录账号密码是否与数据库中一个账号密码相同。相同则返回true，不同则返回false。

};

#endif // DATABASEDATA_H
