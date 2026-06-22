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
	//根据menus生成前端路由
	QList<std::shared_ptr<RouterVo>> BuildMenus(const QList<std::shared_ptr<Menu>>& menus);
	//替换为前端路由格式
	QString InnerLinkReplaceEach(const QString& path);

	QList<std::shared_ptr<Menu>>setChild(const QList<std::shared_ptr<Menu>>& menus,qint32 id);
	QList<std::shared_ptr<Menu>>getChild(const QList<std::shared_ptr<Menu>>& menus,const std::shared_ptr<Menu>& parent);
	void recursionFn(const QList<std::shared_ptr<Menu>>& menus, const std::shared_ptr<Menu>& parent);
	/*std::shared_ptr<Menu> getParent(const std::shared_ptr<Menu>& menu);*/
	bool is_Perm( const std::shared_ptr<Menu>& parent);
	bool is_Child(const QList<std::shared_ptr<Menu>>& menus, const std::shared_ptr<Menu>& parent);
	bool is_ParentView(const std::shared_ptr<Menu>& menu);
	//判断是否为外部链接
	bool is_Externallink(const std::shared_ptr<Menu>& menu);
	//判断是否是菜单内链接
	bool is_MenuFrame(const std::shared_ptr<Menu>& menu);
	//非外链且是一级菜单
	bool is_MenuDir(const std::shared_ptr<Menu>& menu);
	//获取路由名称
	QString getRouteName(const std::shared_ptr<Menu>& menu);
	//获取路由路径
	QString getRoutePath(const std::shared_ptr<Menu>& menu);
	//获取组件
	QString getComponent(const std::shared_ptr<Menu>& menu);
};

