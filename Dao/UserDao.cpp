#include "UserDao.h"
#include "DatabaseMap.h"
#include "Common/Utils/CaptchaMaker.h"
#include <QDateTime>
#include <QSqlError>
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


bool UserDao::register_user(const QString& account, const QString& password, const QSqlDatabase& con)
{
    QSqlQuery query(con);

    query.prepare("INSERT INTO Taoist_temple_user(user_name,nick_name,password,creation_time,creator,online_time) VALUES (?,?,?,?,?,?) ");
    query.bindValue(0,CaptchaMaker::RandomAccount());
    query.bindValue(1, account);
    query.bindValue(2, password);
	query.bindValue(3, QDateTime::currentDateTime().toString("yyyy-MM-dd"));
	query.bindValue(4, account);
	query.bindValue(5, QDateTime::currentDateTime().toString("yyyy-MM-dd HH时"));
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool UserDao::modify_password(const QString& account, const QString& new_password, const QSqlDatabase& con)
{
    QSqlQuery query(con);
    query.prepare("UPDATE Taoist_temple_user SET password = ? WHERE user_name = ?");
    query.bindValue(0, new_password);
    query.bindValue(1, account);
    if (!query.exec()) {
		qDebug() << query.lastError();
		return false;
    }
    return true;
}

bool UserDao::modify_nickName(qint32 id,const QString& nick_name, const QSqlDatabase& con)
{
    QSqlQuery query(con);
    query.prepare("UPDATE Taoist_temple_user SET nick_name = ? WHERE id = ?");
    query.bindValue(0, nick_name);
    query.bindValue(1, id);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool UserDao::modify_avatar(qint32 id,const QString& avatar, const QSqlDatabase& con)
{
    QSqlQuery query(con);

    query.prepare("UPDATE Taoist_temple_user SET avatar = ? WHERE id = ?");
    query.bindValue(0, avatar);
    query.bindValue(1, id);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool UserDao::modify_dateBirth(qint32 id,const QString& date_birth, const QSqlDatabase& con)
{
    QSqlQuery query(con);

    query.prepare("UPDATE Taoist_temple_user SET date_birth = ? WHERE id = ?");
    query.bindValue(0, date_birth);
    query.bindValue(1, id);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool UserDao::modify_gender(qint32 id,const QString& gender, const QSqlDatabase& con)
{
    QSqlQuery query(con);

    query.prepare("UPDATE Taoist_temple_user SET gender = ? WHERE id = ?");
    query.bindValue(0, gender);
    query.bindValue(1, id);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool UserDao::modify_phoneNumber(qint32 id,const QString& phone_number, const QSqlDatabase& con)
{
    QSqlQuery query(con);

    query.prepare("UPDATE Taoist_temple_user SET phone_number = ? WHERE id = ?");
    query.bindValue(0, phone_number);
    query.bindValue(1, id);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool UserDao::delete_user(const QString& password, const QSqlDatabase& con)
{
    QSqlQuery query(con);
    query.prepare("DELETE FROM Taoist_temple_user WHERE password = ?");
    query.bindValue(0, password);
    if (!query.exec()) {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}


