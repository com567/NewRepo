#include "AvatarChooseBox.h"
#include <QWheelEvent>
#include <QPainter>

AvatarChooseBox::AvatarChooseBox(QWidget* parent)
	:QWidget(parent)
{}

AvatarChooseBox::~AvatarChooseBox()
{}

void AvatarChooseBox::setPixmap(const QPixmap& map)
{
	m_CropperImage.pixmap = map;
	m_CropperImage.point = QPoint((width() - map.width()) / 2, (height() - map.height())/2);
	update();
}

QPixmap AvatarChooseBox::getPixmap() const
{
	return m_CropperImage.pixmap;
}

void AvatarChooseBox::zoomIn()
{
	m_CropperImage.scale += 0.1;
	update();
}

void AvatarChooseBox::zoomOut()
{
    m_CropperImage.scale -= 0.1;
    update();
}

void AvatarChooseBox::rotate(float rota)
{
    m_CropperImage.rotate += rota;
}

void AvatarChooseBox::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QPixmap(":/Resources/man.jpg"));
    painter.drawRect(rect());

	if (m_CropperImage.scale != 1) {
		int width = m_CropperImage.pixmap.width() * m_CropperImage.scale;
        int height = m_CropperImage.pixmap.height() * m_CropperImage.scale;

		auto size=m_CropperImage.pixmap.size().scaled(width, height, Qt::KeepAspectRatio);
		if (size != m_CropperImage.pixmap.size()) {
			m_CropperImage.point = {
					(width - size.width()) / 2,
					(height - size.height()) / 2
			};
            m_CropperImage.viewPixmap = m_CropperImage.pixmap.scaled(size,Qt::KeepAspectRatio, Qt::SmoothTransformation);

		}
	}

	painter.drawPixmap(m_CropperImage.point,m_CropperImage.viewPixmap);
}

void AvatarChooseBox::wheelEvent(QWheelEvent* event)
{
	if (event->angleDelta().y() > 0) {
        zoomIn();
	}
	else {
        zoomOut();
	}
}
