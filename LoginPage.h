#pragma once
#include <QtWidgets/QWidget>
#include<QPushButton>
#include "Common/Utils/CaptchaMaker.h"
#include "ui_LoginPage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginPageClass; };
QT_END_NAMESPACE

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    LoginPage(QWidget* parent = nullptr);
    ~LoginPage();
    void switch_interface(QWidget*w);
public slots:
    void on_LoginBtn1_clicked();
    void on_RegBtn1_clicked();
    void on_affirm_clicked();
    void Storage_verificationCode(ClickLabel*label);

protected:
    void paintEvent(QPaintEvent* event)override;
    void resizeEvent(QResizeEvent* event)override;

private:
    Ui::LoginPageClass *ui;
    CaptchaMaker m_Maker;
    QPair<QString, QString>verificationCode{"",""};
    QPair<QString, QString>new_used_password{ "","" };
    QString copy;
    QWidget* widget;
    QPixmap background_;
    int x, y;

    
};

