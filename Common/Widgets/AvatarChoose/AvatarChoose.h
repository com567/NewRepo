#pragma once

#include <QWidget>
#include "ui_AvatarChoose.h"

QT_BEGIN_NAMESPACE
namespace Ui { class AvatarChooseClass; };
QT_END_NAMESPACE

class AvatarChoose : public QWidget
{
	Q_OBJECT

public:
	AvatarChoose(QWidget *parent = nullptr);
	~AvatarChoose();

public slots:
	void on_chooseBtn_clicked();	

protected:
	void resizeEvent(QResizeEvent* event) override;

private:
	
	Ui::AvatarChooseClass *ui;
};

