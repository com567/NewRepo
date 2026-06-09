#include "ClickLabel.h"
#include <QMouseEvent>

ClickLabel::ClickLabel(QWidget *parent)
	: QLabel(parent)
{}

ClickLabel::~ClickLabel()
{}

void ClickLabel::click()
{
    emit clicked();
}



void ClickLabel::enterEvent(QEnterEvent* event)
{
    setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
    QLabel::enterEvent(event);
    emit enter();
}

void ClickLabel::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
	m_pressed=true;
	}
	QLabel::mousePressEvent(event);

}

void ClickLabel::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_pressed) {
        emit clicked();
        m_pressed=false;
    }
    QLabel::mouseReleaseEvent(event);
}

