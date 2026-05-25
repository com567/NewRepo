#include "UserDao.h"
#include "DatabaseMap.h"
#include "../Common/Utils/CaptchaMaker.h"
#include <QDateTime>
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
       return {};
    }

    if (!query.next()) {
        return {};
    }
	auto user=orm::mysql::user::from(query);
    return user;
}

std::shared_ptr<User> UserDao::searchNick_name(const QString& nickname, const QSqlDatabase& con)
{
    QSqlQuery query(con);
    
    query.prepare("SELECT * FROM Taoist_temple_user WHERE nick_name= ?");
    query.bindValue(0, nickname);
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

    query.prepare("INSERT INTO Taoist_temple_user(user_name,nick_name,password,creation_time,creator,online_time) VALUES (?,?,?,?,?,?) ");
    query.bindValue(0,CaptchaMaker::RandomAccount());
    query.bindValue(1, account);
    query.bindValue(2, password);
	query.bindValue(3, QDateTime::currentDateTime().toString("yyyy-MM-dd"));
	query.bindValue(4, account);
	query.bindValue(5, QDateTime::currentDateTime().toString("yyyy-MM-dd"));
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
    QSqlQuery query(con);
}


