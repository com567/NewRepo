#pragma once
#include <QStandardItemModel>
#include <QTreeView>

class Navigation  : public QTreeView
{
	Q_OBJECT

public:
	Navigation(QWidget *parent=nullptr);
	~Navigation();

	void interface();

private:
	QStandardItemModel* m_model;
};

