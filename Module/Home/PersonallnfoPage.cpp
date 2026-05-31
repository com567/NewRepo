#include "PersonallnfoPage.h"
#include "Common/Utils/Utils.h"
#include "Common/Utils/Coating.h"
#include "Entity/User.hpp"
PersonallnfoPage::PersonallnfoPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PersonallnfoPageClass())
{
	ui->setupUi(this);
	Utils::setDropShadow(this);
	Coating::instance()->setViewPort(this);
	Coating::instance()->popup(ui->Function_zone);
	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	connect(ui->closeBtn, &QToolButton::clicked, this, [this] {this->close(); emit sig_return(); });
}

PersonallnfoPage::~PersonallnfoPage()
{
	delete ui;
}

void PersonallnfoPage::setUser(std::shared_ptr<User> user)
{
	if (!user)return;
	if (user->avatar.isEmpty()) {
		ui->avatar->setIcon(QIcon(":/Resources/man.jpg"));
		ui->avatar->setIconSize(iconSize);
	}
	ui->avatar->setIcon(QIcon(user->avatar));
    ui->avatar->setIconSize(iconSize);
    ui->nick_name->setText(user->nickName);
	ui->user_name->setText(user->userName);
	ui->gender->setText(user->gender);
	ui->date_birth->setText(user->dateBirth);
	ui->phone_number->setText(user->phoneNumber);
	ui->creation_time->setText(user->creationTime);
	ui->online_time->setText(user->onlineTime);
}

void PersonallnfoPage::setAvatar(const QIcon& icon)
{
}

void PersonallnfoPage::setNickName(const QString& nick_name)
{
}

void PersonallnfoPage::setGender(const QString& gender)
{
}

void PersonallnfoPage::setBirth(const QString& birth)
{
}

void PersonallnfoPage::setPhone(const QString& phone)
{
}

