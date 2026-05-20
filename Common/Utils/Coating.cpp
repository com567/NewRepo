#include "Coating.h"
#include <QPainter>
#include <QEvent>
#include <QResizeEvent>


Coating::Coating(QWidget *parent)
	: QWidget(parent)
{
	setFocusPolicy(Qt::StrongFocus);
	setFocus();
}

Coating::~Coating()
{}

void Coating::setViewPort(QWidget * view)
{
	if(!view)return;


	m_viewPort = view;
	this->setParent(view); 
	this->hide();
	m_viewPort->installEventFilter(this);
}

QWidget* Coating::getViewPort() const
{
	return nullptr;
}

void Coating::setBackgroundColor(const QColor& color)
{
    m_backgroundColor = color;
}

QColor Coating::getBackgroundColor() const
{
	return m_backgroundColor;
}

void Coating::popup(QWidget* w)
{
	if(!m_viewPort)
        return;

	addWidget(w);

	m_popWidget = w;
	w->setParent(this);
    w->show();
	this->show();
	this->setFocus();
}

bool Coating::eventFilter(QObject* watched, QEvent* event)
{
	if(watched == m_viewPort)
	{ 
		if(!m_popWidget)
            return false;
		if(event->type() == QEvent::Resize)
		{
			auto resizeEvent = static_cast<QResizeEvent*>(event);
			this->setGeometry(QRect(QPoint(0,0), resizeEvent->size()));
		}
	}
	else if(watched == m_popWidget)
	{
		if(event->type() == QEvent::Close||event->type() == QEvent::Hide)
		{
			this->hide();
		}
	}
	return false;
}

void Coating::paintEvent(QPaintEvent* event)
{
	   QPainter painter(this);
       painter.fillRect(rect(),m_backgroundColor);


}

void Coating::resizeEvent(QResizeEvent* event)
{
	int x= (this->width()-m_popWidget->width())/2;
    int y= (this->height()-m_popWidget->height())/2;
    m_popWidget->move(x,y);
}

void Coating::keyPressEvent(QKeyEvent* event)
{
	  if(event->key() == Qt::Key_Escape)
      {
          this->close();
      }
}

void Coating::addWidget(QWidget* w)
{  
	
	auto it=m_widgetSet.insert(w);
	if (it != m_widgetSet.end()) {
         w->installEventFilter(this);
	}
	
	if(m_popWidget)
        m_popWidget->hide();
}

