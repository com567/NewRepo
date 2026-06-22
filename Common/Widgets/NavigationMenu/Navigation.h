#pragma once
#include "Domain/Vo/RouterVo.hpp"
#include <QStandardItemModel>
#include <QTreeView>

class Navigation  : public QTreeView
{
	Q_OBJECT

public:
	Navigation(QWidget *parent=nullptr);
	~Navigation();

	
	void setRouterVo(const QList<std::shared_ptr<RouterVo>>& routers);
signals:
	// 内部路由跳转（以 '/' 开头），由外层界面接收并处理页面切换
	void sigNavigate(const QString& path);

public slots:
	// 处理点击事件
	void onItemClicked(const QModelIndex& index);

private:
	QStandardItemModel* m_model;
};

