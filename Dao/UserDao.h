#pragma once
#include "Common/Base/Singleton.hpp"
#include "SqlConnection.hpp"
#include "Entity/User.hpp"
#include <QSqlDatabase>
#include <QSqlQuery>
class UserDao : public Singleton<UserDao>
{
	friend class Singleton<UserDao>;
public:
	UserDao();
	~UserDao();
	

	std::shared_ptr<User> searchUser_name(const QString&name,const QSqlDatabase&con = getConnection());
    std::shared_ptr<User> searchNick_name(const QString&phone, const QSqlDatabase& con = getConnection());

	bool register_user(const QString& account,const QString& password,const QSqlDatabase& con = getConnection());
	bool modify_password(const QString& account, const QString& new_password, const QSqlDatabase& con = getConnection());
	bool modify_nickName(qint32 id,const QString& nick_name, const QSqlDatabase& con = getConnection());
	bool modify_avatar(qint32 id,const QString& avatar, const QSqlDatabase& con = getConnection());
	bool modify_dateBirth(qint32 id,const QString& date_birth, const QSqlDatabase& con = getConnection());
	bool modify_gender(qint32 id,const QString& gender, const QSqlDatabase& con = getConnection());
	bool modify_phoneNumber(qint32 id,const QString& phone_number, const QSqlDatabase& con = getConnection());
	bool delete_user(const QString& password, const QSqlDatabase& con = getConnection());

};

