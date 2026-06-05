#include "AvatarChoose.h"
#include <QFileDialog>

AvatarChoose::AvatarChoose(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::AvatarChooseClass())
{
	ui->setupUi(this);

}

AvatarChoose::~AvatarChoose()
{
	delete ui;
}

void AvatarChoose::resizeEvent(QResizeEvent* event)
{
	int x = (width() - ui->widget->width()) / 2;
    int y = (height() - ui->widget->height()) / 2;
    ui->widget->move(x, y);
}



void AvatarChoose::on_chooseBtn_clicked() {
	auto filename = QFileDialog::getOpenFileName(this, "选择图片", "./", "Image Files(*.png *.jpg *.bmp)");
	if (filename.isEmpty())return;
	ui->avatarCropper->setPixmap(QPixmap(filename));
}
