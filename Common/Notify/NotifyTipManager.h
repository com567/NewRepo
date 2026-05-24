#pragma once
#include "NotifyTipBox.h"
#include "LoginPage.h"
#include "Common/Base/Singleton.hpp"
#include <QResizeEvent>
#include <QObject>

//通知提示管理器
class NotifyTipManager  : public QObject,public Singleton<NotifyTipManager>
{
	Q_OBJECT
	friend class Singleton<NotifyTipManager>;
public:																	
	NotifyTipManager(QObject *parent=nullptr);
	~NotifyTipManager();

	
	//获取父窗口
	void setViewPort(QWidget* parent);
	QWidget* ViewPort() const;

	NotifyTipBox* addNotifyTip(NotifyTipBox::Message_type type = NotifyTipBox::Login_successfully);
	NotifyTipBox* addNotifyTip(qint32 delay,NotifyTipBox::Message_type type = NotifyTipBox::Login_successfully);
	NotifyTipBox* addNotifyTip(NotifyTipBox& tip);

	
	//设置显示时间
	void setHolder(qint32 ms);
	qint32 holder() const;

public slots:
	void slot_newNotifyTip(NotifyTipBox* tip,int index);
signals:
	void newNotifyTip(NotifyTipBox* tip,int index);

protected:
	bool eventFilter(QObject* obj, QEvent* event) override;
private:
	QList<NotifyTipBox*> m_notifyTips;
	QSize m_notifyTipSize;
	QWidget* m_viewPort{};
	QPoint m_notifyTipPos;
	QPoint m_notifyPos() const;
	qint32 m_holder;
};

