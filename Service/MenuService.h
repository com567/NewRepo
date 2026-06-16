#pragma once
#include "Domain/Vo/RouterVo.hpp"
#include "Dao/MenuDao.h"
class MenuService :public Singleton<MenuService>
{
	friend class Singleton<MenuService>;
public:
	QList<std::shared_ptr<Menu>> GetMenuList();
	QList<std::shared_ptr<Menu>> GetMenuTree();
	QList<std::shared_ptr<RouterVo>> GetRouters();
private:
	QList<std::shared_ptr<RouterVo>> BuildMenus(const QList<std::shared_ptr<Menu>>& menus);
	//替换为前端路由格式
	QString InnerLinkReplaceEach(const QString& path);

	QList<std::shared_ptr<Menu>>setChild(const QList<std::shared_ptr<Menu>>& menus,qint32 id);
	QList<std::shared_ptr<Menu>>getChild(const QList<std::shared_ptr<Menu>>& menus,const std::shared_ptr<Menu>& parent);
	void recursionFn(const QList<std::shared_ptr<Menu>>& menus, const std::shared_ptr<Menu>& parent);
	std::shared_ptr<Menu> getParent(const std::shared_ptr<Menu>& menu);
	bool is_Perm( const std::shared_ptr<Menu>& parent);
	bool is_Child(const QList<std::shared_ptr<Menu>>& menus, const std::shared_ptr<Menu>& parent);
	bool is_Parent(const std::shared_ptr<Menu>& menu);
	bool is_Externallink(const std::shared_ptr<Menu>& menu);
	bool is_MenuFrame(const std::shared_ptr<Menu>& menu);

	QString getRouteName(const std::shared_ptr<Menu>& menu);
	QString getRoutePath(const std::shared_ptr<Menu>& menu);
	QString getComponent(const std::shared_ptr<Menu>& menu);
};

