#pragma once
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QCloseEvent>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QList>

struct TipData {
	QPixmap icon;
	QString msg;
	QColor backgroundColor;	  // 背景色
	QColor textColor;		  // 文字色
	QColor borderColor;		  // 边框色
    
};

class NotifyTipBox  : public QWidget
{
	Q_OBJECT

public:
	enum Message_type {
		Account_isEmpty,				  //输入框为空
		Be_logging_in,					  //登录中
		Login_successfully,				  //登录成功
		Login_failure,					  //登录失败
		Registered_successfully,		  //注册成功
		modify_successfully,			  //修改成功
		Incorrect_account_or_password,	  //账号或密码错误
		Password_invalid,				  //密码无效					  
		VerificationCode_error,			  //验证码错误
		Two_password_entries,
		User_not_Exist
	};
public:
	NotifyTipBox(QWidget *parent=nullptr);
	NotifyTipBox(Message_type type,QWidget *parent = nullptr);
	NotifyTipBox(Message_type type, qint32 delay, QWidget* parent = nullptr);
	~NotifyTipBox();
	
	void setTipData(TipData &data);
	TipData getTipData()const;
	void setMessage_type(Message_type type);
	//给提示框添加动画效果
	void Begin_animate();
	void Update_animate(
		int duration,
		qreal startValue,
		qreal endValue,
		double midPos,
		qreal midValue,
		int loopCount,
		std::function<void()> finishedCallback
	);
	void End_animate();

	void closeEvent(QCloseEvent* event)override;
signals:
	void disappeared(NotifyTipBox* self);
protected:
	void paintEvent(QPaintEvent* event)override;
	void timerEvent(QTimerEvent* event)override;

private:
	int m_timerId;
	TipData m_data;
	qint32 m_delay;
	inline static QList<TipData>m_preDatas{};		 //预设数据
	QPropertyAnimation* m_animation{nullptr};
};

