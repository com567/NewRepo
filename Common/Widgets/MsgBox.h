#pragma once
#include <QDialogButtonBox>
#include <QCloseEvent>
#include <QWidget>
#include "ui_MsgBox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MsgBoxClass; };
QT_END_NAMESPACE

class MsgBox : public QWidget
{
	Q_OBJECT

public:
	enum IconType {
		Error,
        Warning,
	};

	MsgBox(QWidget *parent = nullptr);
    MsgBox(IconType Type, QWidget *parent = nullptr);
	~MsgBox();

	void setIconType(IconType Type);
	IconType getIconType()const;
	void setText(const QString& text);
	QString getText()const;
    void setIcon(const QPixmap&map);
    QPixmap getIcon()const;

protected:
	void JumpTo();
signals:
	void Ok_clicked();
private:
	Ui::MsgBoxClass *ui;
	IconType m_IconType;
	//QPixmap m_iconPixmap; // 原始图标，用于按字体大小缩放

	// 根据当前文本字体调整并设置图标到 ui->Icon
	/*void updateIconScaled();*/
	
};

