#pragma once
#include <QLabel>

class ClickLabel  : public QLabel
{
	Q_OBJECT

public:
	ClickLabel(QWidget *parent=nullptr);
	~ClickLabel();
protected:
	// 鼠标点击事件
    void mousePressEvent(QMouseEvent *event) override;
    // 鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *event) override;
signals:
	void clicked();
private:
	bool m_pressed{false};
};

