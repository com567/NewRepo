#include "Config.h"

Config::Config(const QString& filename)
	:m_settings(filename, QSettings::IniFormat)
{
}

Config::~Config()
{
}

std::unique_ptr<Config> Config::instance()
{
	auto config = std::make_unique<Config>("config.ini");
	if(!config)
		 return nullptr;
    return config;
}

void Config::setValue(const QAnyStringView& key, const QVariant& value)
{
	 m_settings.setValue(key, value);
}

QVariant Config::getValue(const QAnyStringView& key)
{
	return m_settings.value(key);
}

QVariant Config::getValue(const QAnyStringView& key, const QVariant& defaultValue)
{
	return m_settings.value(key, defaultValue);
}

bool Config::contains(QAnyStringView key)
{
	return m_settings.contains(key);
}

void Config::remove(QAnyStringView key)
{
	m_settings.remove(key);
}
