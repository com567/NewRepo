#include "LoginPage.h"
#include "Common/Notify/NotifyTipManager.h"
#include "Common/Widgets/ClickLabel.h"
#include "Common/Utils/Coating.h"
#include "Common/Widgets/MsgBox.h"
#include <QPainter>
LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPageClass()) 
    ,copy("版权归洛杉矶湖人队所有")
    
{
    ui->setupUi(this);

    NotifyTipManager::instance()->setViewPort(this);
    Coating::instance()->setViewPort(this);

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
    static int i = 1;
    NotifyTipManager::instance()->addNotifyTip(NotifyTipBox::Message_type(i % 10));
    i++;

    static MsgBox*box=new MsgBox;
    box->show();

    Coating::instance()->popup(box);
}
void LoginPage::on_RegBtn1_clicked()
{

}

void LoginPage::on_affirm_clicked()
{
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


