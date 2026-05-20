#include "LoginPage.h"
#include "Common/Notify/NotifyTipManager.h"
#include "Common/Widgets/ClickLabel.h"
#include "Common/Utils/Coating.h"
#include "Common/Widgets/MsgBox.h"
#include <QRegularExpression>
#include <QPainter>


LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPageClass()) 
    ,copy("版权归洛杉矶湖人队所有")
    
{
    ui->setupUi(this);

    NotifyTipManager::instance()->setViewPort(this);
    //Coating::instance()->setViewPort(this);

    background_ = QPixmap(":/Resources/man.jpg");
    widget=ui->LoginWiget;
    switch_interface(widget);
    connect(ui->RegBtn2, &QPushButton::clicked, this, [this] { switch_interface(ui->RegWiget); });
    connect(ui->LoginBtn2, &QPushButton::clicked, this, [this] { switch_interface(ui->LoginWiget); });
    connect(ui->return_home, &QPushButton::clicked, this, [this] {switch_interface(ui->LoginWiget); });
    connect(ui->ForgetPasswordBtn, &QPushButton::clicked, this, [this] {switch_interface(ui->ForgetPassword); });
    connect(ui->RegBtn1, &QPushButton::clicked, this, [this] {});
    connect(ui->LoginBtn1, &QPushButton::clicked, this, [this] {});
    connect(ui->verificationCode_2, &ClickLabel::clicked, this, [this] {qDebug() << "忘记密码验证码"; });
    connect(ui->verificationCode_3, &ClickLabel::clicked, this, [this] {qDebug() << "注册验证码"; });
    connect(ui->verificationCode_4, &ClickLabel::clicked, this, 
        [this] {
            auto pr=m_Maker.createText();
            //qDebug() << pr.first << pr.second;
            auto pix=m_Maker.createImage(pr.first);
            ui->verificationCode_4->setPixmap(pix);
        });
}

LoginPage::~LoginPage()
{
    delete ui;
    //Coating::instance()->deleteLater();
}

void LoginPage::switch_interface(QWidget* w)
{   
    if (!w||!ui)return;
               
    if (w == ui->RegWiget) {
        ui->LoginWiget->hide();
        ui->RegWiget->show();
     }
    else if (w == ui->ForgetPassword) {
        ui->LoginWiget->hide();
        ui->ForgetPassword->show();
    }
    else {
        ui->ForgetPassword->hide();
        ui->RegWiget->hide();
        ui->LoginWiget->show();
    }
    w->move(x, y);
}


void LoginPage::on_LoginBtn1_clicked()
{
    /*static int i = 1;
    NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type(i % 10));
    i++;

    static MsgBox* box{};
    if (!box) {
        box = new MsgBox(MsgBox::IconType::Warning);

    }
    box->show();

    Coating::instance()->popup(box);*/

    auto username=ui->User_ID_3->text().trimmed();
    auto password=ui->Print_password->text().trimmed();
    auto verificationCode=ui->verification_4->text().trimmed();
    if(username.isEmpty()||password.isEmpty()||verificationCode.isEmpty())
        NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Account_isEmpty);
    else if(username=="admin"&&password=="917813")
        NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Login_successfully);
    else if(username!="admin"||password!="917813")
        NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Incorrect_account_or_password);
    else if(verificationCode!=m_Maker.createText().first)
        NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::VerificationCode_error);
    else
        NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Login_failure);

}
void LoginPage::on_RegBtn1_clicked()
{
     auto username=ui->User_ID_2->text().trimmed();
     auto password=ui->setNew_password1_2->text().trimmed();
     auto password2=ui->setNew_password2_2->text().trimmed();
     auto verificationCode=ui->verification_3->text().trimmed();
     if(username.isEmpty()||password.isEmpty()||verificationCode.isEmpty())
        NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Account_isEmpty);
     //密码不能少于8位，且必须包含数字和大小写字母
     else if(password.size()<8||!password.contains(QRegularExpression("[0-9]"))||!password.contains(QRegularExpression("[a-zA-Z]")))
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Password_invalid);
     else if(password!=password2)
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Two_password_entries);
     else if(verificationCode!=m_Maker.createText().first)
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::VerificationCode_error);
     else
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Registered_successfully);
     
}

void LoginPage::on_affirm_clicked()
{
     auto username=ui->User_ID->text().trimmed();
     auto password=ui->setNew_password1->text().trimmed();
     auto password2=ui->setNew_password2->text().trimmed();
     auto verificationCode=ui->verification_2->text().trimmed();
     
     if (username.isEmpty() || password.isEmpty() || verificationCode.isEmpty())
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Account_isEmpty);
     //密码不能少于8位，且必须包含数字和大小写字母
     else if (password.size() < 8 || !password.contains(QRegularExpression("[0-9]")) || !password.contains(QRegularExpression("[a-zA-Z]")))
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Password_invalid);
     else if (password != password2)
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Two_password_entries);
     else if (verificationCode != m_Maker.createText().first)
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::VerificationCode_error);
     else
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void LoginPage::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if (!background_.isNull()) {
     painter.drawPixmap(rect(), background_);
    }
    
    painter.setPen(Qt::GlobalColor::red);
    painter.drawText(5,height()-5, copy);
}

void LoginPage::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    if (!ui || !ui->LoginWiget) return;
    x = (width() - ui->LoginWiget->width()) / 2;
    y = (height() - ui->LoginWiget->height()) / 2;
    ui->LoginWiget->move(x, y);
    // 若当前显示的是其它 widget，也可统一处理：
    if (widget) widget->move(x, y);
}


