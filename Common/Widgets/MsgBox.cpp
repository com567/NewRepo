#include "MsgBox.h"

MsgBox::MsgBox(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::MsgBoxClass())
{
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
	connect(ui->CloseBtn, &QToolButton::clicked, this, [this] {this->close(); });
	connect(ui->whetherBtn, &QDialogButtonBox::rejected, this, [this] {this->hide(); });
	connect(ui->whetherBtn, &QDialogButtonBox::accepted, this, [this] {JumpTo(); });

}

MsgBox::~MsgBox()
{
	delete ui;
}

void MsgBox::JumpTo()
{
	qDebug() << "跳转成功";
}


