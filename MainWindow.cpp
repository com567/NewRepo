#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MainWindowClass())
{
	ui->setupUi(this);

	connect(ui->Loginpage, &LoginPage::sig_login_finished, this, 
		[this] {
			ui->stackedWidget->setCurrentWidget(ui->HomePageContainer);
			
		});

}

MainWindow::~MainWindow()
{
	delete ui;
}

