#pragma once

#include "Common/Base/Singleton.hpp"
#include "SqlConnection.hpp"
#include "Domain/Entity/Menu.hpp"
#include <QSqlDataBase>
#include <QList>

class MenuDao :public Singleton<MenuDao>
{
	friend class Singleton<MenuDao>;
public:
	QList<std::shared_ptr<Menu>> GetMenuList(const QSqlDatabase&con=getConnection());
};

