#pragma once
#include<QWidget>

//设置阴影
class Utils 
{
public:
	static void setDropShadow(QWidget* widget);

	QPixmap toRoundPixmap(const QPixmap& pixmap, int radius=-1);
	//在编译期把字符串转为整形常量
	static constexpr unsigned int OptionHash(const char* str, int h = 0) {
        return !str[h] ? 5381 : (OptionHash(str,h +1)*33)^str[h];
	}
	Utils();
	~Utils();
};

