#pragma once

#include <QWidget>
#include "ui_HomePage.h"

class NotifyTipManager;
QT_BEGIN_NAMESPACE
namespace Ui { class HomePageClass; };
QT_END_NAMESPACE

class HomePage : public QWidget
{
	Q_OBJECT

public:
	HomePage(QWidget *parent = nullptr);
	~HomePage();

signals:
	void sig_quit_login();

private:
	Ui::HomePageClass *ui;
	QMenu* m_personalMenu{};
	void initPersonalMenu();
};

