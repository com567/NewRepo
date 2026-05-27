#include "HomePage.h"
#include "MainWindow.h"
HomePage::HomePage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomePageClass())
{
	ui->setupUi(this);
}

HomePage::~HomePage()
{
	delete ui;
}

