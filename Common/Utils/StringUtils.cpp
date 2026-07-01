#include "StringUtils.h"
#include <QRegularExpression>
bool StringUtils::is_HttpUrl(const QString& url)
{
	return (url.startsWith("http://") || url.startsWith("https://"));
}

QString StringUtils::Capitalize_FirstLetter(const QString& str)
{
	if (str.isEmpty())return QString();
	auto s = str;
	s.front() = s.front().toUpper();
	return s;
}

bool StringUtils::is_Password(const QString& str)
{
	
	if (str.size()>8 && str.contains(QRegularExpression("[0-9]")) && str.contains(QRegularExpression("[a-z]")) && str.contains(QRegularExpression("[A-Z]")))
		return true;
    else
        return false;

}
