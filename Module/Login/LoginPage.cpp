#include "Common/Widgets/ClickLabel.h"
#include "Common/Widgets/MsgBox.h"
#include "ContextHolder.h"
#include "MainWindow.h"
#include <QRegularExpression>
#include <QPainter>


LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPageClass()) 
    , copy("版权归洛杉矶湖人队所有")
    , config(Config::instance())
    
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);
    background_ = QPixmap(":/Resources/man.jpg");
    widget=ui->LoginWiget;
    switch_interface(widget);
    connect(ui->RegBtn2, &QPushButton::clicked, this, [this] { switch_interface(ui->RegWiget); });
    connect(ui->LoginBtn2, &QPushButton::clicked, this, [this] { switch_interface(ui->LoginWiget); });
    connect(ui->return_home, &QPushButton::clicked, this, [this] {switch_interface(ui->LoginWiget); });
    connect(ui->ForgetPasswordBtn, &QPushButton::clicked, this, 
        [this] 
        {   switch_interface(ui->ForgetPassword);
            ui->User_ID->setText(config->getValue("Account/account_number").toString());
        });
    connect(ui->RegBtn1, &QPushButton::clicked, this, [this] {});
    connect(ui->LoginBtn1, &QPushButton::clicked, this, [this] {});
    connect(ui->verificationCode_2, &ClickLabel::clicked, this,
        [this] {
            Storage_verificationCode(ui->verificationCode_2);
            
        });
    connect(ui->verificationCode_3, &ClickLabel::clicked, this, 
        [this] {
            Storage_verificationCode(ui->verificationCode_3);
            
        });
    connect(ui->verificationCode_4, &ClickLabel::clicked, this,
        [this] {
            Storage_verificationCode(ui->verificationCode_4);
        });
    ui->verificationCode_4->click();
    ui->verificationCode_3->click();
    ui->verificationCode_2->click();


    ui->User_ID_3->setText(config->getValue("Account/account_number").toString());
    ui->Print_password->setText(config->getValue("Account/password").toString());
    ui->checkBox_1->setChecked(config->getValue("Account/remember_password").toBool());
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
    auto account_number= ui->User_ID_3->text().trimmed();
    auto password= ui->Print_password->text().trimmed();
    auto input_verificationCode=ui->verification_4->text().trimmed();
    
    if (account_number.isEmpty() || password.isEmpty()|| input_verificationCode.isEmpty()) {
       NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Account_isEmpty);
       return;
    }
    
	auto user = UserService::instance()->searchUser_name(account_number);
    
    if (!user||account_number != user->userName||password != user->password) {
        NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Incorrect_account_or_password);
        return;
    }

    else if (input_verificationCode != verificationCode.second){
         {
            NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::VerificationCode_error);
            return;
        }
    }
    else {
        
        config->setValue("Account/account_number",account_number);
        
        if (ui->checkBox_1->isChecked()) { 
            config->setValue("Account/password", password);
            config->setValue("Account/remember_password",ui->checkBox_1->isChecked());
        }
        else {
            config->remove("Account/password");
            config->remove("Account/remember_password");
        }
            ContextHolder::instance()->setSelf(user);
            emit sig_login_finished();
    }
            
}

void LoginPage::on_RegBtn1_clicked()
{
     auto input_nick_name=ui->User_ID_2->text().trimmed();
     new_used_password.first = ui->setNew_password1_2->text().trimmed();
     new_used_password.second= ui->setNew_password2_2->text().trimmed();
     auto input_verificationCode=ui->verification_3->text().trimmed();
     if (input_nick_name.isEmpty() || new_used_password.first.isEmpty() || input_verificationCode.isEmpty() ||
         new_used_password.second.isEmpty()) {
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Account_isEmpty);
         return;
     }
        

     //密码不能少于8位，且必须包含数字和大小写字母
     else if (new_used_password.first.size() < 8 || !new_used_password.first.contains(QRegularExpression("[0-9]")) ||
         !new_used_password.first.contains(QRegularExpression("[a-zA-Z]"))) {
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Password_invalid);
         return;
     }
         

     else if (new_used_password.first != new_used_password.second) {
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Two_password_entries);
         return;
     }
         

     else if (input_verificationCode != verificationCode.second) {
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::VerificationCode_error);
         return;
        
     }

     else {
         if (UserService::instance()->register_user(input_nick_name, new_used_password.first)) {
             NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Registered_successfully);
             return;
         }
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Registered_failure);
     }
         
         
     
}

void LoginPage::on_affirm_clicked()
{
     auto input_username=ui->User_ID->text().trimmed();
     new_used_password.first = ui->setNew_password1->text().trimmed();
     new_used_password.second = ui->setNew_password2->text().trimmed();
     auto input_verificationCode=ui->verification_2->text().trimmed();

     auto user = UserService::instance()->searchUser_name(input_username);
     if (!user) {
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::User_not_Exist);
         return;
     }
     
     else if (input_username.isEmpty() || new_used_password.first.isEmpty() || input_verificationCode.isEmpty()) {
          NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Account_isEmpty);
          return;

     }
     //密码不能少于8位，且必须包含数字和大小写字母
     else if (new_used_password.first.size() < 8 || !new_used_password.first.contains(QRegularExpression("[0-9]")) ||
         !new_used_password.first.contains(QRegularExpression("[a-zA-Z]"))) {
          NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Password_invalid);
          return;

     }

     else if (new_used_password.first != new_used_password.second){
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::Two_password_entries);
         return;

     }

     else if (input_verificationCode != verificationCode.second) {
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::VerificationCode_error);
         return;

     }

     else
         NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type::modify_successfully);
}

void LoginPage::Storage_verificationCode(ClickLabel* label)
{     
        verificationCode = m_Maker.createText();     
        auto pix = m_Maker.createImage(verificationCode.first);
        label->setPixmap(pix);
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


