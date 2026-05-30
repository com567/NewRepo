#include "MsgBox.h"

MsgBox::MsgBox(QWidget *parent)
	:MsgBox(IconType::Warning, parent)
{
	

}

MsgBox::MsgBox(IconType Type, QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MsgBoxClass())
    , m_IconType(Type)
{
	ui->setupUi(this);
	setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

	setIconType(m_IconType);
	connect(ui->CloseBtn, &QToolButton::clicked, this, [this] {this->close(); });
	connect(ui->whetherBtn, &QDialogButtonBox::rejected, this, [this] {this->hide(); });
	connect(ui->whetherBtn, &QDialogButtonBox::accepted, this, [this] { });
}

MsgBox::~MsgBox()
{
	delete ui;
}

void MsgBox::setIconType(IconType Type)
{
	
	if(Type == IconType::Warning){
	setText("是否要进行修改?(学生身份信息极为重要，请谨慎修改)");
	setIcon(QPixmap(":/Resources/warn_icon.svg"));
	}
	else if(Type == IconType::Error){
	setText("发生错误!");
	setIcon(QPixmap(":/Resources/false_alarm.svg"));
	}
	else return;

}

MsgBox::IconType MsgBox::getIconType() const
{
	return m_IconType;
}

void MsgBox::setText(const QString& text)
{
    ui->Hint_text->clear();
	ui->Hint_text->setText(text);
}

QString MsgBox::getText() const
{
	return ui->Hint_text->text();
}

void MsgBox::setIcon(const QPixmap& map)
{
    ui->Icon->clear();
    ui->Icon->setPixmap(map);
}

QPixmap MsgBox::getIcon() const
{
    return ui->Icon->pixmap();
}


