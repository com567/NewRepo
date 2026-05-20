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


//parent==loginpage
void NotifyTipManager::setViewPort(QWidget* parent)
{
	if (!parent)return;
	// 如果已有视口，先移除旧的事件过滤器
	if (m_viewPort && m_viewPort != parent) {
		m_viewPort->removeEventFilter(this);
		if (auto oldWin = m_viewPort->window()) oldWin->removeEventFilter(this);
	}

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
	if (!m_viewPort) return false;

	// 处理视口自身的 Resize，或顶层窗口/视口的 Move（窗口移动时需要重新定位提示）
	if (obj == m_viewPort || obj == m_viewPort->window()) {
		if (event->type() == QEvent::Resize || event->type() == QEvent::Move) {
			// 重新计算居中位置
			m_notifyTipPos.rx() = (m_viewPort->width() - m_notifyTipSize.width()) / 2;
			m_notifyTipPos.ry() = 40;

			// 将所有已创建且可见的提示框移动到新的位置
			for (auto tip : m_notifyTips) {
				if (!tip) continue;
				// 仅移动当前属于视口的并且可见的提示框
				if (tip->parent() == m_viewPort && tip->isVisible()) {
					tip->move(m_notifyPos());
				}
			}
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
		tip->setFixedSize(m_notifyTipSize);
		tip->move(m_notifyPos());

		tip->show();
		
		tip->Begin_animate();	 
}

