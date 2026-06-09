#include "AvatarChooseBox.h"
#include <QWheelEvent>
#include <QPainter>

AvatarChooseBox::AvatarChooseBox(QWidget* parent)
	:QWidget(parent)
	,m_TailorRect(QRect((width() - 100) / 2, (height() - 100) / 2, 100, 100))
	,m_TailorPoint((width() - 100) / 2, (height() - 100) / 2)
{}

AvatarChooseBox::~AvatarChooseBox()
{}

void AvatarChooseBox::setPixmap(const QPixmap& map)
{
	m_CropperImage.pixmap = map;
	m_CropperImage.viewPixmap = map;
	m_CropperImage.point=QPoint(- map.width() / 2, - map.height() / 2);
	update();
}

QPixmap AvatarChooseBox::getPixmap() const
{
	return m_CropperImage.pixmap;
}

void AvatarChooseBox::tailor()
{
	m_isTailor = !m_isTailor;
	update();
}

void AvatarChooseBox::zoomIn()
{
	if (m_CropperImage.scale > 5.0)return;
	m_CropperImage.scale += 0.05;
	update();
}

void AvatarChooseBox::zoomOut()
{
	if(m_CropperImage.pixmap.size().width() * m_CropperImage.scale<=size().width()||
		m_CropperImage.pixmap.size().height()<=size().height())return;
    m_CropperImage.scale -= 0.05;
    update();
}

void AvatarChooseBox::rotate(float rota)
{
	m_CropperImage.rotate += rota;
	update();
}

void AvatarChooseBox::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton&&rect().contains(event->pos())) {
		if (!m_isTailor) {
			m_isPressed = true;
			m_Offset= event->pos()-m_CropperImage.point;
		}
		else
			m_faceOffset = event->pos() - m_TailorRect.topLeft();
	}
event->accept();
}

void AvatarChooseBox::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPressed) {
		m_CropperImage.point = event->pos() - m_Offset;
	}
	else if (m_isTailor) {
		m_TailorRect.moveTopLeft(event->pos() - m_faceOffset);
		if(m_TailorRect.left() < 0)
            m_TailorRect.moveLeft(0);
		else if(m_TailorRect.right() > width())
            m_TailorRect.moveRight(width());
        if(m_TailorRect.top() < 0)
            m_TailorRect.moveTop(0);
		else if(m_TailorRect.bottom() > height())
            m_TailorRect.moveBottom(height());
	}
	update();
    event->accept();
}

void AvatarChooseBox::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		m_isPressed = false;
		event->accept();
	}
}

void AvatarChooseBox::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);

	QPainter painter(this);
	auto bg=Background();
    painter.drawPixmap(0, 0, bg);
	if (m_isTailor) {
		QColor darkColor(0, 0, 0, 140);
		painter.fillRect(rect(), darkColor);
		painter.drawPixmap(m_TailorRect,bg, m_TailorRect);
        painter.setPen(Qt::red);
        painter.drawRect(m_TailorRect);
		emit pixmapChanged(bg.copy(m_TailorRect));
	}
	else
        emit pixmapChanged(bg);
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

void AvatarChooseBox::resizeEvent(QResizeEvent* event)
{
	m_TailorRect = QRect((width() - 100) / 2, (height() - 100) / 2, 100, 100);
}

QPixmap AvatarChooseBox::Background()
{
	QPixmap pix(this->size());
	QPainter painter(&pix);
	painter.setPen(Qt::NoPen);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.setBrush(QBrush(Qt::lightGray));
	auto r = rect();
	// 平移坐标轴到控件中心
	painter.translate(r.center());

	
	painter.drawRect(QRect(-r.width() / 2, -r.height() / 2, r.width(), r.height()));
	if (m_CropperImage.pixmap.isNull())return pix;
	if (m_CropperImage.scale != 1) {
		int targetW = qMax(1, int(m_CropperImage.pixmap.width() * m_CropperImage.scale));
		int targetH = qMax(1, int(m_CropperImage.pixmap.height() * m_CropperImage.scale));
		QSize targetSize(targetW, targetH);
		if (targetSize != m_CropperImage.viewPixmap.size()) {
			// 使用 KeepAspectRatio 保持比例且平滑转换
			m_CropperImage.point = QPoint(-targetSize.width() / 2, -targetSize.height() / 2);
			m_CropperImage.viewPixmap = m_CropperImage.pixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
		}
	}
	painter.rotate(m_CropperImage.rotate);
	painter.drawPixmap(m_CropperImage.point, m_CropperImage.viewPixmap);
	return pix;
}
