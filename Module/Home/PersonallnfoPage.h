#pragma once

#include <QWidget>
#include "Common/Notify/NotifyTipManager.h"
#include "ui_PersonallnfoPage.h"
#include "ContextHolder.h"
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
	void setAvatar(const QString& icon);
	void setNickName(const QString& nick_name);
	void setGender(const qint8& gender);
	void setBirth(const QString& birth);
	void setPhone(const QString& phone);

private:
	Ui::PersonallnfoPageClass *ui;
	NotifyTipManager*m_notifyTipManager;
	QSize iconSize{101,91};


	QWidget*avatarWidget();
    void birthWidget();
    QWidget*phoneWidget();
};

