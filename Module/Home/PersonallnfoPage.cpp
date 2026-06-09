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
	//ui->avatar->setMakLayer(true);
	Utils::setDropShadow(this);
	NotifyTipManager::instance()->setViewPort(ui->Function_zone);

	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	setUser(ContextHolder::instance()->getSelf());

	connect(ui->birth, &ClickLabel::clicked, this, [this] {birthWidget(); });
	connect(ui->closeBtn, &QToolButton::clicked, this, [this] {this->close();});
	connect(ui->avatar,&ClickLabel::clicked, this, [this] {on_avatar_clicked(); });
	connect(ui->nick_name,&QLineEdit::editingFinished,this,[this] {setNickName(ui->nick_name->text()); });
	connect(ui->genderBtn, &QComboBox::currentTextChanged, this, [this] {setGender(qint8(ui->genderBtn->currentIndex())); });
	
}

PersonallnfoPage::~PersonallnfoPage()
{
	delete ui;
}

void PersonallnfoPage::setUser(std::shared_ptr<User> user)
{
	if (!user)return;
	if (user->avatar.isEmpty()) {
		ui->avatar->setPixmap(QPixmap(":/Resources/man.jpg"));
		ui->avatar->setScaledContents(true);
	}
	else
	ui->avatar->setPixmap(QPixmap(user->avatar));
	ui->avatar->setScaledContents(true);
	ui->nick_name->setText(user->nickName);
	ui->user_name->setText(user->userName);
	ui->genderBtn->setCurrentIndex(user->gender);
	ui->date_birth->setText(user->dateBirth);
	ui->phone_number->setText(user->phoneNumber);
	ui->creation_time->setText(user->creationTime);
	ui->online_time->setText(user->onlineTime);
}

void PersonallnfoPage::setAvatarPath(const QString& icon)
{
	if (!UserService::instance()->modify_avatar(icon)) {
		NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return ;
	}
	ContextHolder::instance()->getSelf()->avatar = icon;
}

void PersonallnfoPage::setAvatar(const QPixmap& pix)
{
	ui->avatar->setPixmap(pix);
	NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::setNickName(const QString& nick_name)
{
	if (!UserService::instance()->modify_nickName(nick_name)) {
		NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}

	ui->nick_name->setText(nick_name);
	ContextHolder::instance()->getSelf()->nickName = nick_name;
	NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
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
		NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}
	ContextHolder::instance()->getSelf()->gender = gender;
	NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::setBirth(const QString& birth)
{
	
	if (!UserService::instance()->modify_dateBirth(birth)) {
		NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}

	ui->date_birth->setText(birth);
    ContextHolder::instance()->getSelf()->dateBirth = birth;
	NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::setPhone(const QString& phone)
{
	if (!UserService::instance()->modify_phoneNumber(phone)) {
		NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_failure);
		return;
	}

	ui->phone_number->setText(phone);
	NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void PersonallnfoPage::resizeEvent(QResizeEvent* event)
{
	int x=(this->width()-ui->Function_zone->width())/2;
	int y=(this->height()-ui->Function_zone->height())/2;
    ui->Function_zone->move(x,y);
}




void PersonallnfoPage::on_avatar_clicked() {
	
	m_avatarChoose=new AvatarChoose(this);
	connect(m_avatarChoose, &AvatarChoose::sig_avatar_affirm,this,
		[this](QPixmap& pix) {
				setAvatar(pix);
		});
	connect(m_avatarChoose, &AvatarChoose::sig_avatar_path, this,
		[this](QString& path) {
			setAvatarPath(path);
		});

	m_avatarChoose->showMaximized();
	
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



