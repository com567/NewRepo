#include "Personallnfo/PersonallnfoPage.h"
#include "Service/MenuService.h"
#include "MainWindow.h"
#include <QDesktopServices>
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
	ui->NavBar->setRouterVo(MenuService::instance()->GetRouters());
	connect(ui->NavBar, &Navigation::sigNavigate, this, &HomePage::onNavigate);
}

HomePage::~HomePage()
{
	delete ui;
}


void HomePage::onNavigate(const QString& path)
{
	// 外链（以 http(s) 开头）用系统浏览器打开（Navigation 已处理，但这里做保险判断）
	if (path.startsWith("http://", Qt::CaseInsensitive) || path.startsWith("https://", Qt::CaseInsensitive)) {
		QDesktopServices::openUrl(QUrl(path));
		return;
	}
	// 规范化路径
	QString p = path;
	if (p.isEmpty()) p = "/";
	if (!p.startsWith("/")) p = "/" + p;

	// 典型映射示例：根据路由 path 切换 stackedWidget 页面
	// 请根据实际路由命名调整判定条件或改为映射表
	if (p == "/" || p == "/mainpage") {
		ui->Content->setCurrentWidget(ui->mainpage);
		return;
	}
	if (p == "/personlinfopage" || p.contains("person")) {
		ui->Content->setCurrentWidget(ui->personlinfopage);
		return;
	}

	// 通用尝试：按 objectName 匹配 stacked widget 的页面（去掉前导 '/')
	QString name = p.mid(1);
	for (int i = 0; i < ui->Content->count(); ++i) {
		QWidget* w = ui->Content->widget(i);
		if (w && w->objectName() == name) {
			ui->Content->setCurrentIndex(i);
			return;
		}
	}

	// 兜底：回到主页面
	ui->Content->setCurrentWidget(ui->mainpage);
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

