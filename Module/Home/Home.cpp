#include "Home.h"

Home::Home(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomeClass())
{
	ui->setupUi(this);
}

Home::~Home()
{
	delete ui;
}

