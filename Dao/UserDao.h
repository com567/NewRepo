#pragma once
#include "../Common/Base/Singleton.hpp"
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

	void searchUser_name(const QString&name,const QSqlDatabase&con);
    void searchNick_name(const QString&phone, const QSqlDatabase& con);
};

