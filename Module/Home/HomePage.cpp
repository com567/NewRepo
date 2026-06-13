#include "Personallnfo/PersonallnfoPage.h"
#include "MainWindow.h"
#include <QMenu>
HomePage::HomePage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomePageClass())
{
	ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground);
	ui->Content->setCurrentWidget(ui->mainpage);
	NotifyTipManager::instance()->setViewPort(this);
	initPersonalMenu();
	connect(ui->Head_portrait, &ClickLabel::enter, this, [this]() {
		if(m_personalMenu->isHidden())
		{
			QPoint pos(ui->Head_portrait->x() - ui->Head_portrait->width() - 20, ui->Head_portrait->y() + ui->Head_portrait->height());
			pos = ui->RightBar->mapToGlobal(pos);
			m_personalMenu->popup(pos);
		}
		});
	
}

HomePage::~HomePage()
{
	delete ui;
}

void HomePage::AvatarChanged()
{
	auto user=ContextHolder::instance()->getSelf();
	if(!user||user->avatar.isEmpty())
		ui->Head_portrait->setPixmap(QPixmap(":/Resources/man.jpg"));
	else {
		auto path=Config::instance()->profilePath()+"/"+user->avatar;
		ui->Head_portrait->setPixmap(QPixmap(path));
	}
	
	ui->Head_portrait->setScaledContents(true);
}

void HomePage::resizeEvent(QResizeEvent* event)
{
	ui->Head_portrait->setFixedSize(80, 80);
}

void HomePage::initPersonalMenu()
{
	
	m_personalMenu=new QMenu(this);
	m_personalMenu->setFixedSize(250, 135);
	m_personalMenu->addSeparator();
	m_personalMenu->addAction("个人中心", [this] {
		auto personallnfoPage = new PersonallnfoPage;
		connect(personallnfoPage, &PersonallnfoPage::sig_avatar_update, this, [this](const QPixmap& pixmap)
			{
				ui->Head_portrait->setPixmap(pixmap);
				ui->Head_portrait->setScaledContents(true);
			});
		personallnfoPage->showMaximized();
		});
	m_personalMenu->addSeparator();
	m_personalMenu->addAction("实名认证", [this] {
		NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::IconType::Warning, "实名认证功能暂未开放");
		});
    m_personalMenu->addSeparator();
	m_personalMenu->addAction("安全设置");
	m_personalMenu->addSeparator();
	m_personalMenu->addAction("帮助与反馈");
    m_personalMenu->addSeparator();
	m_personalMenu->addAction("退出登录", [this] {emit sig_quit_login(); });

}

