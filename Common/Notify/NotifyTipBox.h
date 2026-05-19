#pragma once
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include<QTimerEvent>
#include <QWidget>
#include<QPainter>
#include<QList>

struct TipData {
	QPixmap icon;
	QString msg;
	qint32 delay;
	QColor backgroundColor;	  // 背景色
	QColor textColor;		  // 文字色
	QColor borderColor;		  // 边框色
    
};

class NotifyTipBox  : public QWidget
{
	Q_OBJECT

public:
	enum Message_type {
		Account_isEmpty,
		Login_successfully,
		Registered_successfully,
		modify_successfully,
		Wrong_password,
		Password_invalid,
		User_exists,
		User_Notexists,
		VerificationCode_error,
		Login_failure
	};
public:
	NotifyTipBox(QWidget *parent=nullptr);
	NotifyTipBox(Message_type type,QWidget *parent = nullptr);
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
signals:
	void disappeared(NotifyTipBox* self);
protected:
	void paintEvent(QPaintEvent* event)override;
	void timerEvent(QTimerEvent* event)override;

private:
	int m_timerId;
	TipData m_data;
	inline static QList<TipData>m_preDatas{};		 //预设数据
	QPropertyAnimation* m_animation{nullptr};
};

