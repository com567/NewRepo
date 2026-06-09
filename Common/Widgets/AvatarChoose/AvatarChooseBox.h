#pragma once
#include <QWidget>
class AvatarChooseBox :	public QWidget
{
	Q_OBJECT
public:
	AvatarChooseBox(QWidget *parent = nullptr);
	~AvatarChooseBox();

	void setPixmap(const QPixmap& map);
	QPixmap getPixmap()const;
	void tailor();
	void zoomIn();
    void zoomOut();
	void rotate(float rota);
	

protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
signals:
    void pixmapChanged(const QPixmap);
private:
	struct CropperIamge {
		QPixmap pixmap;
		QPixmap viewPixmap;
		QPoint point;
		float scale{1.0};	//缩放比例
		float rotate{0};	//旋转角度
	}m_CropperImage;

	bool m_isPressed{false};
	QPoint m_Offset;
    QPoint m_faceOffset;
	bool m_isTailor{false};
    QPoint m_TailorPoint;
	QRect m_TailorRect;


	QPixmap Background();
};

