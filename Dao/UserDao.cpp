#include "UserDao.h"
#include "DatabaseMap.h"

UserDao::UserDao()
{}

UserDao::~UserDao()
{}


std::shared_ptr<User> UserDao::searchUser_name(const QString & name, const QSqlDatabase & con)
{
    QSqlQuery query(con);
    query.prepare("SELECT * FROM Taoist_temple_user WHERE user_name= ?");
    query.bindValue(0, name);
    if(!query.exec())
    {
       qDebug() << query.lastError();
    }

    if (!query.next()) {
        return {};
    }
	auto user=orm::mysql::user::from(query);
    return user;
}

std::shared_ptr<User> UserDao::searchNick_name(const QString& phone, const QSqlDatabase& con)
{
    QSqlQuery query(con);
    query.prepare("SELECT * FROM Taoist_temple_user WHERE nick_name= ?");
    query.bindValue(0, phone);
    if(!query.exec())
    {
        qDebug() << query.lastError();
    }

    if (!query.next()) {
		return {};
    }
	auto user=orm::mysql::user::from(query);
    return user;
}

void UserDao::register_user(const QString& account, const QString& password, const QSqlDatabase& con)
{
    QSqlQuery query(con);
    query.prepare("INSERT INTO Taoist_temple_user(user_name,password) VALUES (?,?) ");
    query.bindValue(0, account);
    query.bindValue(1, password);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return;
    }

}

void UserDao::modify_password(const QString& account, const QString& new_password, const QSqlDatabase& con)
{
    QSqlQuery query(con);
}

void UserDao::modify_nickName(const QString& nick_name, const QSqlDatabase& con)
{
    QSqlQuery query(con);
}

void UserDao::modify_dateBirth(const QString& date_birth, const QSqlDatabase& con)
{
    QSqlQuery query(con);
}

void UserDao::modify_gender(const QString& gender, const QSqlDatabase& con)
{
    //QSqlQuery query(con);
}

