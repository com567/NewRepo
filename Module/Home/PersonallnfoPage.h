#pragma once

#include <QWidget>
#include "ui_PersonallnfoPage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class PersonallnfoPageClass; };
QT_END_NAMESPACE

class PersonallnfoPage : public QWidget
{
	Q_OBJECT

public:
	PersonallnfoPage(QWidget *parent = nullptr);
	~PersonallnfoPage();

private:
	Ui::PersonallnfoPageClass *ui;
};

