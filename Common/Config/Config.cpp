#include "Config.h"
#include <QStandardPaths>
#include <QFile>
#include <QDir>

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

    if (!config->contains("app/profile")) {
        QString path;
        // 优先放 D 盘，否则放到用户目录下的一个默认位置
        if (QFile::exists("D:/")) {
            path = QDir::fromNativeSeparators(QStringLiteral("D:/HdyStudentManager/user/avatar"));
        }
        else {
            path = QDir::fromNativeSeparators(
                QStandardPaths::writableLocation(QStandardPaths::HomeLocation)
                + QStringLiteral("/HdyStudentManager/user/avatar"));
        }

        QDir dir;
        if (!dir.exists(path)) {
            dir.mkpath(path); // 创建整个路径
        }

        config->setValue("app/profile", path);
        // 立即写盘以便观察
        config->m_settings.sync();
    }

    return config;
}

void Config::setValue(const QAnyStringView& key, const QVariant& value)
{
	 m_settings.setValue(key, value);
     m_settings.sync();
}

QVariant Config::getValue(const QAnyStringView& key)
{
	return m_settings.value(key);
}

QVariant Config::getValue(const QAnyStringView& key, const QVariant& defaultValue)
{
	return m_settings.value(key, defaultValue);
}

QString Config::profilePath() const
{
    return QDir::fromNativeSeparators(m_settings.value("app/profile").toString());
}

bool Config::contains(QAnyStringView key)
{
	return m_settings.contains(key);
}

void Config::remove(QAnyStringView key)
{
	m_settings.remove(key);
	m_settings.sync();
}
