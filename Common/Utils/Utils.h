#pragma once
#include<QWidget>

//设置阴影
class Utils 
{
public:
	static void setDropShadow(QWidget* widget);

	QPixmap toRoundPixmap(const QPixmap& pixmap, int radius=-1);

	Utils();
	~Utils();
};

