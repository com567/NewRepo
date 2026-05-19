#pragma once
#include "Common/Base/Singleton.hpp"

#include <QWidget>

//遮蔽层
class Coating  : public QWidget,public Singleton<Coating>
{
	Q_OBJECT

	friend class Singleton<Coating>;
public:
	Coating(QWidget *parent=nullptr);
	~Coating();

	void setViewPort(QWidget* view);
	QWidget* getViewPort()const;

    void setBackgroundColor(const QColor&color);
    QColor getBackgroundColor()const;

	void popup(QWidget*w);
protected:
	bool eventFilter(QObject *watched, QEvent *event)override;
    void paintEvent(QPaintEvent *event)override;
	void resizeEvent(QResizeEvent *event)override;
	void keyPressEvent(QKeyEvent *event)override;
private:
	QWidget* m_viewPort{};
	QWidget* m_popWidget{};
	QWidgetSet m_widgetSet;
	QColor m_backgroundColor{205,205,205,100};
};

