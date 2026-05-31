#pragma once

#include <QWidget>
#include "ui_PersonallnfoPage.h"
struct User;
QT_BEGIN_NAMESPACE
namespace Ui { class PersonallnfoPageClass; };
QT_END_NAMESPACE

class PersonallnfoPage : public QWidget
{
	Q_OBJECT

public:
	PersonallnfoPage(QWidget *parent = nullptr);
	~PersonallnfoPage();
	void setUser(std::shared_ptr<User>user);
	void setAvatar(const QIcon& icon);
	void setNickName(const QString& nick_name);
	void setGender(const QString& gender);
	void setBirth(const QString& birth);
	void setPhone(const QString& phone);
signals:
	void sig_return();
private:
	Ui::PersonallnfoPageClass *ui;
	QSize iconSize{101,91};
};

