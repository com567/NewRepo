#pragma once
#include <QLabel>

class ClickLabel  : public QLabel
{
	Q_OBJECT

public:
	ClickLabel(QWidget *parent=nullptr);
	~ClickLabel();
	void click();
protected:


	//鼠标悬停事件
	void enterEvent(QEnterEvent *event) override;
	// 鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override;
    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
	void clicked();
	void enter();
private:
	bool m_pressed{false};
	QPixmap m_pixmap;
};

