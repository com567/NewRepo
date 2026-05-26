#pragma once
#include <QString>
#include <QSettings>
#include <QVariant>

class Config
{
	
public:	 
	Config(const QString& filename);
	~Config();
	static std::unique_ptr<Config> instance();
	 
	void setValue(const QAnyStringView& key, const QVariant& value);
    QVariant getValue(const QAnyStringView& key);
	QVariant getValue(const QAnyStringView& key, const QVariant& defaultValue);
	bool contains( QAnyStringView key);
	void remove(QAnyStringView key);
private:
	QSettings m_settings;

};