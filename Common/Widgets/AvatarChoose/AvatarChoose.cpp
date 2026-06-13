
#include "AvatarChoose.h"
#include <QFileDialog>

AvatarChoose::AvatarChoose(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::AvatarChooseClass())
	,m_ratio(0)
{
	ui->setupUi(this);

	connect(ui->close, &QPushButton::clicked, this,[this]{this->close();});
	connect(ui->tailor, &QPushButton::clicked, this, [this] {ui->avatarCropper->tailor(); });
	connect(ui->amplifier,&QPushButton::clicked,this,[this]{ui->avatarCropper->zoomIn();});
    connect(ui->reduce, &QPushButton::clicked, this, [this]{ui->avatarCropper->zoomOut();});
	connect(ui->clockwise, &QPushButton::clicked, this, [this] {ui->avatarCropper->rotate(m_ratio+=90); });
	connect(ui->anticlockwise, &QPushButton::clicked, this, [this] {ui->avatarCropper->rotate(m_ratio-=90); });
	connect(ui->avatarCropper, &AvatarChooseBox::pixmapChanged, this, [this](const QPixmap& pixmap) 
		{
			ui->avatar->setPixmap(pixmap); 
			//让图标填满
            ui->avatar->setScaledContents(true);
		});

	connect(ui->affirmBtn, &QPushButton::clicked, this, [this] 
		{
		 QPixmap p = ui->avatar->pixmap();
			if (!p.isNull()) {
				// 发射按 const QPixmap& 的信号（已在头文件修改）
				emit sig_avatar_affirm(p);
			}
			this->close();
			this->deleteLater();
		});
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
	//m_path=filename;
	ui->avatarCropper->setPixmap(filename);
}
