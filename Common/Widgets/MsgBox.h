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
	MsgBox(QWidget *parent = nullptr);
	~MsgBox();


protected:
	void JumpTo();
signals:
	void Ok_clicked();
private:
	Ui::MsgBoxClass *ui;
};

