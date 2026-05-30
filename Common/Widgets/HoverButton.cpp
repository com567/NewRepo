#include "HoverButton.h"

HoverButton::HoverButton(QWidget *parent)
	: QPushButton(parent)
{
	setAttribute(Qt::WA_StyledBackground);
}

HoverButton::~HoverButton()
{}

void HoverButton::enterEvent(QEnterEvent * event)
{
	setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
	emit enter();
	
}

void HoverButton::leaveEvent(QEvent* event)
{
	setCursor(QCursor(Qt::CursorShape::ArrowCursor));
    emit leave();
    
}

