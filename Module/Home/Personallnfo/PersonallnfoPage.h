#pragma once
#include "Common/Widgets/AvatarChoose/AvatarChoose.h"
#include "Common/Notify/NotifyTipManager.h"
#include "ui_PersonallnfoPage.h"
#include "Common/Config/Config.h"
#include "ContextHolder.h"
#include <QWidget>
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
	void setAvatar(const QPixmap& pix);
	void setNickName(const QString& nick_name);
	void setGender(const qint8& gender);
	void setBirth(const QString& birth);
	void setPhone(const QString& phone);

public slots:
	void on_avatar_clicked();
signals:
	void sig_avatar_update(const QPixmap&);
protected:
	void resizeEvent(QResizeEvent *event) override;
private:
	Ui::PersonallnfoPageClass *ui;
	AvatarChoose*m_avatarChoose;
    void birthWidget();
    QWidget*phoneWidget();
};

