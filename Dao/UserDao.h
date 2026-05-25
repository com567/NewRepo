#pragma once
#include "../Common/Base/Singleton.hpp"
#include "SqlConnection.hpp"
#include "DatabaseMap.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
class UserDao : public Singleton<UserDao>
{
	friend class Singleton<UserDao>;
public:
	UserDao();
	~UserDao();

	void static printUser(const std::shared_ptr<User>& user) {
		if (!user) {
			qDebug() << "用户不存在";
			return;
		}
		qDebug() << user->id;
		qDebug() << user->userName;
		qDebug() << user->nickName;
		qDebug() << user->password;
		qDebug() << user->gender;
		qDebug() << user->creationTime;
		qDebug() << user->onlineTime;
		qDebug() << user->phoneNumber;
		qDebug() << user->dateBirth;
	}

	std::shared_ptr<User> searchUser_name(const QString&name,const QSqlDatabase&con = getConnection());
    std::shared_ptr<User> searchNick_name(const QString&phone, const QSqlDatabase& con = getConnection());
	void register_user(const QString& account,const QString& password,const QSqlDatabase& con = getConnection());
	void modify_password(const QString& account, const QString& new_password, const QSqlDatabase& con = getConnection());
	void modify_nickName(const QString& nick_name, const QSqlDatabase& con = getConnection());
	void modify_dateBirth(const QString& date_birth, const QSqlDatabase& con = getConnection());
	void modify_gender(const QString& gender, const QSqlDatabase& con = getConnection());



};

