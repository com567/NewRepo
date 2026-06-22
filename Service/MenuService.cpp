#include "Common/Constants/UserConstant.hpp"
#include "Common/Utils/StringUtils.h"
#include "MenuService.h"

QList<std::shared_ptr<Menu>> MenuService::GetMenuList()
{

	return MenuDao::instance()->GetMenuList();
}

QList<std::shared_ptr<Menu>> MenuService::GetMenuTree()
{
	auto menus = MenuDao::instance()->GetMenuList();
	return setChild(menus, 0);
}

QList<std::shared_ptr<RouterVo>> MenuService::GetRouters()
{
	return BuildMenus(GetMenuTree());
}

QList<std::shared_ptr<RouterVo>> MenuService::BuildMenus(const QList<std::shared_ptr<Menu>>& menus)
{
	//qDebug() << InnerLinkReplaceEach("https://box.iduoyu.net/music/?msclkid=1528703c84041b8889a31a0dc4588d80");
	//替换后
	//"box/iduoyu/net/music/?msclkid=1528703c84041b8889a31a0dc4588d80"
	QList<std::shared_ptr<RouterVo>> routers;
	for (auto& menu : menus) {
		auto router = std::make_shared<RouterVo>();
		router->hidden = (menu->is_visible!=1);
		router->name= getRouteName(menu);
		router->path = getRoutePath(menu);
        router->component = getComponent(menu);
		router->meta = std::make_shared<MetaVo>(menu->function_name, menu->path);
		if (menu->children.size() > 0 &&menu->menu_type==UserConstant::TYPE_DIR) {
			router->rdeirct = UserConstant::NO_REDIRECT;
			router->children= BuildMenus(menu->children);
		}
		else if (is_MenuFrame(menu)) {
			std::shared_ptr<RouterVo> child=std::make_shared<RouterVo>();
			child->path = menu->path;
			child->component = menu->component;
			child->name = StringUtils::Capitalize_FirstLetter(menu->path);
            child->meta = std::make_shared<MetaVo>(menu->function_name, menu->path);
            router->children.append(child);
		}
		else if (!is_Externallink(menu)&&menu->parent_id==0) {
			router->meta= std::make_shared<MetaVo>(menu->function_name, menu->path);
			router->path = "/";
			std::shared_ptr<RouterVo> child=std::make_shared<RouterVo>();
			child->path = InnerLinkReplaceEach(menu->path);
			child->component = UserConstant::INNER_LINK;
			child->name = StringUtils::Capitalize_FirstLetter(menu->path);
			child->meta = std::make_shared<MetaVo>(menu->function_name, menu->path);
			router->children.append(child);
		}
        routers.append(router);
	}
	return routers;
}

QString MenuService::InnerLinkReplaceEach(const QString& path)
{
	static const char*before[] = {"http://","https://",".","/"};
    static const char*after[] = {"","","/","/"};
	auto str = path;
	for (int i = 0; i < sizeof(before) / sizeof(before[0]); i++) {
        str = str.replace(before[i], after[i]);
	}
	return str;
}


QList<std::shared_ptr<Menu>> MenuService::setChild(const QList<std::shared_ptr<Menu>>& menus, qint32 id)
{
	QList<std::shared_ptr<Menu>> menuList;
	for (auto& menu : menus) {
		if (menu->parent_id == id) {
			recursionFn(menus, menu);
			menuList.append(menu);
		}
	}
	return menuList;
}

QList<std::shared_ptr<Menu>> MenuService::getChild(const QList<std::shared_ptr<Menu>>& menus,const std::shared_ptr<Menu>& parent)
{
	QList<std::shared_ptr<Menu>> menuList;
	if (!parent) return menuList;
	for (auto& menu : menus) {
		if (menu->parent_id == parent->function_id) {
			menuList.append(menu);
		}
	}
	return menuList;
}

void MenuService::recursionFn(const QList<std::shared_ptr<Menu>>& menus, const std::shared_ptr<Menu>& parent)
{
	if (!parent) return;
	auto children = getChild(menus, parent);
		for (auto& menu : children) {
			if (is_Child(menus, menu)) {
				recursionFn(menus, menu);
				
			}
		}
	parent->children = children;
}

//std::shared_ptr<Menu> MenuService::getParent(const std::shared_ptr<Menu>& menu)
//{
//	if (!is_Perm(menu))
//		return nullptr;
//	//return MenuDao::instance()->GetMenuById(menu->parent_id);
//}

bool MenuService::is_Perm(const std::shared_ptr<Menu>& parent)
{
	if(!parent) return false;
	if (parent->parent_id == 0)
		return false;

	return true;
}

bool MenuService::is_Child(const QList<std::shared_ptr<Menu>>& menus, const std::shared_ptr<Menu>& parent)
{
	if (!parent) return false;
	for (auto& menu : menus) {
		if (menu->parent_id == parent->function_id) {
			return true;
		}
	}
	return false;
}

bool MenuService::is_ParentView(const std::shared_ptr<Menu>& menu)
{
	return (menu->parent_id != 0&&menu->menu_type==UserConstant::TYPE_DIR);
}

bool MenuService::is_Externallink(const std::shared_ptr<Menu>& menu)
{
	if (!menu) return false;
	return (menu->is_frame && StringUtils::is_HttpUrl(menu->path));
}

bool MenuService::is_MenuFrame(const std::shared_ptr<Menu>& menu)
{
	if (!menu) return false;
	return (!menu->is_frame&& menu->parent_id == 0 && menu->menu_type == UserConstant::TYPE_MENU);
}

bool MenuService::is_MenuDir(const std::shared_ptr<Menu>& menu)
{
	return (!menu->is_frame && menu->parent_id == 0 && menu->menu_type == UserConstant::TYPE_DIR);
}

QString MenuService::getRouteName(const std::shared_ptr<Menu>& menu)
{
	if (!menu) return QString();
	auto routeName = StringUtils::Capitalize_FirstLetter(menu->path);
	if (is_MenuDir(menu)) {
		routeName.clear();
	}
	return routeName;
}

QString MenuService::getRoutePath(const std::shared_ptr<Menu>& menu)
{
	if (!menu) return QString("/");
	auto routePath = menu->path;
	if (is_Externallink(menu)&&menu->parent_id!=0) {
		routePath = InnerLinkReplaceEach(routePath);
	}
	else if (is_MenuDir(menu)) {
		routePath = "/"+menu->path;
	}
	else
		routePath = "/";
	return routePath;
}

QString MenuService::getComponent(const std::shared_ptr<Menu>& menu)
{
	if(!menu||menu->component.isEmpty())return UserConstant::LAYOUT;
	auto component = menu->component;
    if (menu->parent_id!=0&&!is_Externallink(menu)) {
        component = UserConstant::INNER_LINK;
	}
	else if (is_ParentView(menu)) {
		component = UserConstant::PARENT_VIEW;
	}
	return component;
}
