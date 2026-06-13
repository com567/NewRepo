#pragma once
#include "Dao/UserDao.h"
class UserService :public Singleton<UserService>
{
	friend class Singleton<UserService>;
public:
	UserService();
	~UserService();

	std::shared_ptr<User> searchUser_name(const QString& name );
	std::shared_ptr<User> searchNick_name(const QString& nick_name);
	bool register_user(const QString& account, const QString& password );
	bool modify_password(const QString& account, const QString& new_password );
	bool modify_nickName(const QString& nick_name );
	bool modify_avatar(qint32 id, const QByteArray& data, const QString& format = "jpg");
	bool modify_dateBirth(const QString& date_birth );
	bool modify_gender(const QString& gender );
	bool modify_phoneNumber(const QString& phone_number );
	bool delete_user(const QString& password );


private:
	std::shared_ptr<UserDao> userService{ UserDao::instance() };
};