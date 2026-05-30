#include "PersonallnfoPage.h"
#include "Common/Utils/Utils.h"
PersonallnfoPage::PersonallnfoPage(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::PersonallnfoPageClass())
{
	ui->setupUi(this);
	setAttribute(Qt::WA_StyledBackground);
	Utils::setDropShadow(this);
	connect(ui->closeBtn, &QToolButton::clicked, this, [this] {ui->Function_zone->close(); });
}

PersonallnfoPage::~PersonallnfoPage()
{
	delete ui;
}

