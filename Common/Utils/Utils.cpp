#include "Utils.h"
#include <QGraphicsDropShadowEffect>

void Utils::setDropShadow(QWidget* widget)
{
	if (!widget)return;
	widget->setAttribute(Qt::WA_TranslucentBackground);
	auto shadow = new QGraphicsDropShadowEffect;
	shadow->setColor(Qt::black);
	shadow->setBlurRadius(5);
    shadow->setOffset(0, 0);
    widget->setGraphicsEffect(shadow);
}

Utils::Utils()
{}

Utils::~Utils()
{}

