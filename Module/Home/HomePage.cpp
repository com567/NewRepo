#include "Module/FunctionMenu/MenuMgrPage.h"
#include "Personallnfo/PersonallnfoPage.h"
#include "Common/Utils/StringUtils.h"
#include "Service/MenuService.h"
#include "Common/Utils/Utils.h"
#include "MainWindow.h"
#include <QDesktopServices>
#include <QMenu>
HomePage::HomePage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomePageClass())
{
	ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground);
	ui->Content->setCurrentWidget(ui->home);
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
	connect(ui->NavBar,&QTreeView::clicked,this, &HomePage::slot_cut_path);
	connect(ui->NavBar, &Navigation::navigationChanged, this, [this](const QStringList& list) {
		if (list.isEmpty())
			ui->navLocationLab->clear();
		else
			ui->navLocationLab->setText(list.join(" / "));
		    ui->navLocationLab->setFont(QFont("黑体", 14));
		});
	ui->NavBar->setRouterVo(MenuService::instance()->GetRouters());
	//connect(ui->NavBar, &Navigation::sigNavigate, this, &HomePage::onNavigate);
}

HomePage::~HomePage()
{
	delete ui;
}


//void HomePage::onNavigate(const QString& path)
//{
//	// 外链（以 http(s) 开头）用系统浏览器打开（Navigation 已处理，但这里做保险判断）
//	if (path.startsWith("http://", Qt::CaseInsensitive) || path.startsWith("https://", Qt::CaseInsensitive)) {
//		QDesktopServices::openUrl(QUrl(path));
//		return;
//	}
//	// 规范化路径
//	QString p = path;
//	if (p.isEmpty()) p = "/";
//	if (!p.startsWith("/")) p = "/" + p;
//
//	// 典型映射示例：根据路由 path 切换 stackedWidget 页面
//	// 请根据实际路由命名调整判定条件或改为映射表
//	if (p == "/" || p == "/mainpage") {
//		ui->Content->setCurrentWidget(ui->mainpage);
//		return;
//	}
//	if (p == "/personlinfopage" || p.contains("person")) {
//		ui->Content->setCurrentWidget(ui->personlinfopage);
//		return;
//	}
//
//	// 通用尝试：按 objectName 匹配 stacked widget 的页面（去掉前导 '/')
//	QString name = p.mid(1);
//	for (int i = 0; i < ui->Content->count(); ++i) {
//		QWidget* w = ui->Content->widget(i);
//		if (w && w->objectName() == name) {
//			ui->Content->setCurrentIndex(i);
//			return;
//		}
//	}
//
//	// 兜底：回到主页面
//	ui->Content->setCurrentWidget(ui->mainpage);
//}

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

void HomePage::setCurrentPage(const QString& path, const QString& title)
{
    if (path.isEmpty()||title.isEmpty())return;
	auto page=new QWidget;
	switch (Utils::OptionHash(qPrintable(path))) {
		case Utils::OptionHash("/system/1/com"):
			//page=addPage<Home>(title);
			break;
		case Utils::OptionHash("/system/management/user"):
			page=addPage<MenuMgrPage>(title);
			break;
		case Utils::OptionHash("/system/2/com"):
            page=addPage<QWidget>(title);
			break;
		case Utils::OptionHash("/system/3/com"):
			page=addPage<QWidget>(title);
			break;
		case Utils::OptionHash("/system/4/com"):
			page=addPage<QWidget>(title);
			break;
		default:
			break;
	}
	if(page)
		ui->Content->setCurrentWidget(page);
}

void HomePage::resizeEvent(QResizeEvent* event)
{
	ui->Head_portrait->setFixedSize(80, 80);
}

void HomePage::slot_cut_path(const QModelIndex& index)
{
	if(!index.isValid())return;
	auto router = index.data(Qt::UserRole).value<std::shared_ptr<RouterVo>>();
	// 防止 router 或其 meta 为 nullptr 导致解引用崩溃
	if (!router || !router->meta) return;
	auto name = router->meta->title;
	if (name == "首页") {

	}

	if (StringUtils::is_HttpUrl(router->meta->link)) {
		if (QDesktopServices::openUrl(QUrl(router->meta->link)))
            return;
		
		else {
			NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::IconType::Warning, "打开链接失败");
			return;
		}

	}
	setCurrentPage(router->meta->link, router->meta->title);
}



void HomePage::initPersonalMenu()
{
	
	m_personalMenu=new QMenu(this);
	m_personalMenu->setFixedSize(250, 135);
	m_personalMenu->addSeparator();
	m_personalMenu->addAction("个人中心", [this] {
		if (m_personalInfoPage) {
			if (m_personalInfoPage->isMinimized())
				m_personalInfoPage->showNormal();
			m_personalInfoPage->raise();
			m_personalInfoPage->activateWindow();
			return;
		}

		// 首次创建
		m_personalInfoPage = new PersonallnfoPage;
		// 关闭时自动 delete，QPointer 会在对象销毁后自动置为 nullptr
		m_personalInfoPage->setAttribute(Qt::WA_DeleteOnClose);

		connect(m_personalInfoPage, &PersonallnfoPage::sig_avatar_update, this, [this](const QPixmap& pixmap)
			{
				ui->Head_portrait->setPixmap(pixmap);
				ui->Head_portrait->setScaledContents(true);
			});
		m_personalInfoPage->showMaximized();
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

