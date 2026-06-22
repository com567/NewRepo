#pragma once
#include <QString>

//路由元数据
struct MetaVo {
	QString title; //标题
	//QString icon;
	QString link;  //链接

	MetaVo() = default;
	MetaVo(const QString& title, const QString& link)
		:title(title)
		//, icon(icon)

	{
		if(link.isEmpty())
            this->link = "/";
		else if (link.startsWith("http://") || link.startsWith("https://")) {
            this->link = link;
		}
        else {
            this->link = "/" + link;
        }
	}
};