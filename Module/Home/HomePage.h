#pragma once

#include <QWidget>
#include "ui_HomePage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HomePageClass; };
QT_END_NAMESPACE

class HomePage : public QWidget
{
	Q_OBJECT

public:
	HomePage(QWidget *parent = nullptr);
	~HomePage();

private:
	Ui::HomePageClass *ui;
};

