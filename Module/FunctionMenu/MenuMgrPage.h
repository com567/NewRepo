#pragma once

#include <QWidget>
#include "ui_MenuMgrPage.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuMgrPageClass; };
QT_END_NAMESPACE

class MenuMgrPage : public QWidget
{
	Q_OBJECT

public:
	MenuMgrPage(QWidget *parent = nullptr);
	~MenuMgrPage();


public slots:
	void on_ResetBtn_clicked();
	void on_searchBtn_clicked();


private:
	Ui::MenuMgrPageClass *ui;
	QStandardItemModel* m_model{};
};

