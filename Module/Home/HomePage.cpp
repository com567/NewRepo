#include "MainWindow.h"
#include "PersonallnfoPage.h"
#include "ContextHolder.h"
#include <QMenu>
HomePage::HomePage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomePageClass())
{
	ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground);
	ui->Content->setCurrentWidget(ui->mainpage);
	initPersonalMenu();
	connect(ui->Head_portrait, &HoverButton::enter, this, [this]() {
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

void HomePage::initPersonalMenu()
{
	
	m_personalMenu=new QMenu(this);
	m_personalMenu->setFixedSize(250, 135);
	m_personalMenu->addSeparator();
	m_personalMenu->addAction("个人中心", [this] {
		auto user_data = new PersonallnfoPage();
		user_data->showMaximized();
		ui->personlinfopage->setUser(ContextHolder::instance()->getSelf()
		);});
	m_personalMenu->addSeparator();
    m_personalMenu->addAction("实名认证");
    m_personalMenu->addSeparator();
	m_personalMenu->addAction("安全设置");
	m_personalMenu->addSeparator();
	m_personalMenu->addAction("帮助与反馈");
    m_personalMenu->addSeparator();
	m_personalMenu->addAction("退出登录",this, &HomePage::sig_quit_login);

}

