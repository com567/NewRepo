#include "HoverButton.h"
#include <QMouseEvent>
#include <QPainter>

HoverButton::HoverButton(QWidget *parent)
	: QPushButton(parent)
	,m_MakLayer{false}
{
	setAttribute(Qt::WA_StyledBackground);
	
}

HoverButton::~HoverButton()
{}

void HoverButton::setMakLayer(bool enabled)
{
	m_MakLayer = enabled;
}

bool HoverButton::getMakLayer() const
{
	return m_MakLayer;
}

void HoverButton::setAvatarIcon(const QIcon& icon)
{
    m_avatarIcon = icon;
}

void HoverButton::setAvatarIconSize(const QSize& size)
{
	m_avatarIconSize = size;
}

QIcon HoverButton::getAvatarIcon() const
{
	return m_avatarIcon;
}

QSize HoverButton::getAvatarIconSize() const
{
	return m_avatarIconSize;
}

void HoverButton::enterEvent(QEnterEvent * event)
{
	setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
	update();
	emit enter();
	
}

void HoverButton::leaveEvent(QEvent* event)
{
	setCursor(QCursor(Qt::CursorShape::ArrowCursor));
	update();
    emit leave();	

}

void HoverButton::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.drawPixmap(rect(),m_avatarIcon.pixmap(rect().size()));

}

