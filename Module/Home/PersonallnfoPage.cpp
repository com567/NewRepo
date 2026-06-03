
#include "Common/Utils/Coating.h"
#include "Service/UserService.h"
#include "Common/Utils/Utils.h"
#include "PersonallnfoPage.h"
#include "Entity/User.hpp"
#include <QCalendarWidget>
#include <QPainter>

PersonallnfoPage::PersonallnfoPage(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::PersonallnfoPageClass())
{
	ui->setupUi(this);
	ui->avatar->setMakLayer(true);

	Utils::setDropShadow(this);
	Coating::instance()->setViewPort(this);
	Coating::instance()->popup(ui->Function_zone);
	m_notifyTipManager = NotifyTipManager::instance();
	m_notifyTipManager->setViewPort(this);


	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setUser(ContextHolder::instance()->getSelf());

	connect(ui->closeBtn, &QToolButton::clicked, this, [this] {this->close();});
	/*connect(ui->avatar, &HoverButton::enter, this, [this] {ui->avatar->setMakLayer(true); });
    connect(ui->avatar, &HoverButton::leave, this, [this] {ui->avatar->setMakLayer(false); });*/
	connect(ui->nick_name,&QLineEdit::editingFinished,this,[this] {setNickName(ui->nick_name->text()); });
	connect(ui->genderBtn, &QComboBox::currentTextChanged, this, [this] {setGender(qint8(ui->genderBtn->currentIndex())); });
	connect(ui->birth, &ClickLabel::clicked, this, [this] {birthWidget(); });
}

PersonallnfoPage::~PersonallnfoPage()
{
	delete ui;
}

void PersonallnfoPage::setUser(std::shared_ptr<User> user)
{
	if (!user)return;
	if (user->avatar.isEmpty()) {
		
		ui->avatar->setAvatarIcon(QIcon(":/Resources/man.jpg"));
		ui->avatar->setAvatarIconSize(iconSize);
	}
	else
	ui->avatar->setAvatarIcon(QIcon(user->avatar));

	ui->avatar->setIconSize(iconSize);
	ui->nick_name->setText(user->nickName);
	ui->user_name->setText(user->userName);
	ui->genderBtn->setCurrentIndex(user->gender);
	ui->date_birth->setText(user->dateBirth);
	ui->phone_number->setText(user->phoneNumber);
	ui->creation_time->setText(user->creationTime);
	ui->online_time->setText(user->onlineTime);
}

void PersonallnfoPage::setAvatar(const QString& icon)
{
	if (!UserService::instance()->modify_avatar(icon)) {
		m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}

	ui->avatar->setIcon(QIcon(icon));
	m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::setNickName(const QString& nick_name)
{
	if (!UserService::instance()->modify_nickName(nick_name)) {
		m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}

	ui->nick_name->setText(nick_name);
	ContextHolder::instance()->getSelf()->nickName = nick_name;
	m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::setGender(const qint8& gender)
{
	QString genderStr;
	if (gender == 0)
		genderStr = "";
	else if (gender == 1)
		genderStr = "男";
	else if (gender == 2)
		genderStr = "女";
	else
		return;
	if (!UserService::instance()->modify_gender(genderStr)) {
		m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}
	ContextHolder::instance()->getSelf()->gender = gender;
	m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::setBirth(const QString& birth)
{
	
	if (!UserService::instance()->modify_dateBirth(birth)) {
		m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}

	ui->date_birth->setText(birth);
    ContextHolder::instance()->getSelf()->dateBirth = birth;
	m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::setPhone(const QString& phone)
{
	if (!UserService::instance()->modify_phoneNumber(phone)) {
		m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}

	ui->phone_number->setText(phone);
	m_notifyTipManager->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}



QWidget* PersonallnfoPage::avatarWidget()
{
	QWidget* widget = new QWidget(this);
	QPainter painter(widget);


	return widget;
}



void PersonallnfoPage::birthWidget()
{
	QCalendarWidget* cal = new QCalendarWidget(nullptr);
	cal->setWindowFlags(Qt::Popup);
	QPoint p = ui->birth->mapToGlobal(QPoint(0, ui->birth->height()));
	cal->move(p);
	connect(cal, &QCalendarWidget::clicked, this, [this, cal](const QDate& d) {
		QString birthStr = d.toString("yyyy-MM-dd");
		this->setBirth(birthStr);
		cal->deleteLater();
		});
	cal->show();
}

QWidget* PersonallnfoPage::phoneWidget()
{
	QWidget* widget = new QWidget(this);
	return widget;
}



