#pragma once
#include "ui_MainWindow.h"
#include "Service/UserService.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

signals:
	void sig_login_success();
private:
	Ui::MainWindowClass *ui;
};

