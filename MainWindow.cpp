#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MainWindowClass())
{
	ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground);
	NotifyTipManager::instance()->setViewPort(this);
	ui->stackedWidget->setCurrentWidget(ui->LoginPageContainer);
	connect(ui->Loginpage, &LoginPage::sig_login_finished, this, 
		[this] {
			ui->stackedWidget->setCurrentWidget(ui->HomePageContainer);
			emit sig_login_success();
		});

	connect(this, &MainWindow::sig_login_success, ui->Homepage, [this] {
		NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Login_successfully);
		});

	connect(ui->Homepage, &HomePage::sig_quit_login, this, 
		[this] {
			ui->stackedWidget->setCurrentWidget(ui->LoginPageContainer);
			NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::IconType::Success,"退出成功");
		});

}

MainWindow::~MainWindow()
{
	delete ui;
}


