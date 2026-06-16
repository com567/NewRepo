#include "StringUtils.h"

bool StringUtils::is_HttpUrl(const QString& url)
{
	return (url.startsWith("http://") || url.startsWith("https://"));
}

QString StringUtils::Capitalize_FirstLetter(const QString& str)
{
	if(str.isEmpty())return QString();
	auto s=str;
	s.front()=s.front().toUpper();
	return s;
}
