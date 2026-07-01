#include "Utils.h"
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>
#include <QModelIndex>
#include <QPainter>

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

bool Utils::isParent(const QModelIndex& child, const QModelIndex& parent)
{
	if (child.isValid())
		return false;
	auto parentIndex = child.parent();
	while (parentIndex.isValid()) {
		if (parent == parentIndex) {
			return true;
		}
		parentIndex = parentIndex.parent();
	}
	return false;
}

int Utils::parentCount(const QModelIndex& index)
{
	int count = 0;
	auto parentIndex = index.parent();
	while (parentIndex.isValid()) {
		++count;
		parentIndex = parentIndex.parent();
	}
	return count;
}

Utils::Utils()
{}

Utils::~Utils()
{}

