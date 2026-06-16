#include "MenuDao.h"
#include "Dao/DatabaseMap.h"

QList<std::shared_ptr<Menu>> MenuDao::GetMenuList(const QSqlDatabase& con)
{
	QSqlQuery query(con);
	query.prepare("SELECT * FROM Function_menu WHERE is_active = 1 order by parent_id,order_num");
	if (!query.exec()) {
		qDebug() << "MenuDao::GetMenuList error:" << query.lastError().text();
		return {};
	}

	QList<std::shared_ptr<Menu>> menuList;
	while (query.next()) {
		menuList.append(orm::mysql::menu::from(query));
	}

	return menuList;
}
