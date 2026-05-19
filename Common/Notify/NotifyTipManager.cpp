#include "NotifyTipManager.h"
#include<QWidget>
#include <QDebug>
#include <QEvent>

NotifyTipManager::NotifyTipManager(QObject *parent)
	: QObject(parent)
	,m_holder(2000)
	,m_notifyTipSize(420,60)
{
connect(this, &NotifyTipManager::newNotifyTip, this, &NotifyTipManager::slot_newNotifyTip);
}

NotifyTipManager::~NotifyTipManager()
{
	
}



void NotifyTipManager::setViewPort(QWidget* parent)
{
	if (!parent)return;
	if (m_viewPort != parent) {
	  m_viewPort = parent;
	  m_viewPort->installEventFilter(this);
	}
	
}

QWidget* NotifyTipManager::ViewPort() const
{
	return m_viewPort;
}

void NotifyTipManager::addNotifyTip(NotifyTipBox::Message_type type)
{
	auto T=m_notifyTips.emplaceBack(new NotifyTipBox(type));
	emit newNotifyTip(T,m_notifyTips.size()-1);
}


void NotifyTipManager::addNotifyTip(NotifyTipBox& tip)
{	   
	auto T=m_notifyTips.emplaceBack(&tip);
    emit newNotifyTip(T,m_notifyTips.size()-1);
}



void NotifyTipManager::setHolder(qint32 ms)
{
    	m_holder = ms;
}

qint32 NotifyTipManager::holder() const
{
	return m_holder;
}



bool NotifyTipManager::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == m_viewPort) {
		if (event->type() == QEvent::Resize) {
			m_notifyTipPos.rx() = (m_viewPort->width() - m_notifyTipSize.width()) / 2;
			m_notifyTipPos.ry() = 40;
	   }
	}
	return false;
}

QPoint NotifyTipManager::m_notifyPos() const
{
	return QPoint(m_notifyTipPos.x(), m_notifyTipPos.y());
}


void NotifyTipManager::slot_newNotifyTip(NotifyTipBox* tip, int index) {
	if (!ViewPort())
	{
		qDebug() << "ViewPort is null";
		return;
	}

		tip->setParent(m_viewPort);
		tip->move(m_notifyPos());
		tip->setFixedSize(m_notifyTipSize);
		tip->show();
		tip->Begin_animate();	 
}

