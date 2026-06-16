#pragma once
#include <QString>

class StringUtils 
{
public:
	static bool is_HttpUrl(const QString& url);
	static QString Capitalize_FirstLetter(const QString& str);
};

