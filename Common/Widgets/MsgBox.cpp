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
	connect(ui->whetherBtn, &QDialogButtonBox::accepted, this, [this] {JumpTo(); });
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
	//先擦除掉原来的图标
    ui->Icon->clear(); 
    ui->Icon->setPixmap(map);
	ui->Icon->adjustSize();
}

QPixmap MsgBox::getIcon() const
{
    return ui->Icon->pixmap();
}

//void MsgBox::updateIconScaled()
//{
//	if (m_iconPixmap.isNull()) {
//		ui->Icon->clear();
//		return;
//	}
//
//	// 以 Hint_text 的字体高度作为目标高度，给出一些上下边距
//	QFontMetrics fm(ui->Hint_text->font());
//	int textHeight = fm.height();
//	int targetHeight = qMax(16, textHeight); // 最小高度保证可见
//
//	qreal dpr = this->devicePixelRatioF();
//	QSize targetSize(targetHeight, targetHeight);
//
//	// 使用物理像素创建和缩放，然后设置 devicePixelRatio
//	QPixmap scaled = m_iconPixmap;
//	if (scaled.devicePixelRatioF() != dpr) {
//		scaled.setDevicePixelRatio(dpr);
//	}
//	scaled = scaled.scaled(targetSize * dpr, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//	scaled.setDevicePixelRatio(dpr);
//
//	ui->Icon->setFixedSize(targetSize);
//	ui->Icon->setPixmap(scaled);
//}

void MsgBox::JumpTo()
{
	qDebug() << "跳转成功";
}


