#include "UserDao.h"

UserDao::UserDao()
{}

UserDao::~UserDao()
{}

void UserDao::searchUser_name(const QString & name, const QSqlDatabase & con)
{
    QSqlQuery query(con);
    query.prepare("SELECT * FROM taoist_temple_user WHERE user_name=:name");
    query.bindValue(0, name);
    if(!query.exec())
    {
       qDebug() << query.lastError();
    }

}

void UserDao::searchNick_name(const QString& phone, const QSqlDatabase& con)
{
    QSqlQuery query(con);
    query.prepare("SELECT * FROM taoist_temple_user WHERE nick_name=:name");
    query.bindValue(":name", phone);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }
}

