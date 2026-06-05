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
	void zoomIn();
    void zoomOut();
	void rotate(float rota);

protected:
	void paintEvent(QPaintEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
private:
	struct CropperIamge {
		QPixmap pixmap;
		QPixmap viewPixmap;
		QPoint point;
		float scale{1.0};	//缩放比例
		float rotate;	//旋转角度
	}m_CropperImage;
};

