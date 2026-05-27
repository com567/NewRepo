#pragma once
#include "Common/Base/Singleton.hpp"
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
	//严重性	代码	说明	项目	文件	行	抑制状态	详细信息
	//错误	C2061	语法错误 : 标识符“LoginPage”	D : \_Q2026\HdyStudentManager\out\build\debug\HdyStudentManager	D : \_Q2026\HdyStudentManager\out\build\debug\HdyStudentManager_autogen\include\ui_MainWindow.h	49

	/*void static printUser(const std::shared_ptr<User>& user) {
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
	}*/

	std::shared_ptr<User> searchUser_name(const QString&name,const QSqlDatabase&con = getConnection());
    std::shared_ptr<User> searchNick_name(const QString&phone, const QSqlDatabase& con = getConnection());


	bool register_user(const QString& account,const QString& password,const QSqlDatabase& con = getConnection());
	bool modify_password(const QString& account, const QString& new_password, const QSqlDatabase& con = getConnection());
	bool modify_nickName(const QString& nick_name, const QSqlDatabase& con = getConnection());
	bool modify_avatar(const QString& avatar, const QSqlDatabase& con = getConnection());
	bool modify_dateBirth(const QString& date_birth, const QSqlDatabase& con = getConnection());
	bool modify_gender(const QString& gender, const QSqlDatabase& con = getConnection());
	bool modify_phoneNumber(const QString& phone_number, const QSqlDatabase& con = getConnection());
	bool delete_user(const QString& password, const QSqlDatabase& con = getConnection());

};

