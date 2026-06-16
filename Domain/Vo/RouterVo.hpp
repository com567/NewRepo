#pragma once
#include "Domain/Vo/MetaVo.hpp"
#include <QString>
#include <QList>

struct RouterVo {
	QString name;
    QString path;
    QString rdeirct;
    QString component;
    bool hidden;
    std::shared_ptr<MetaVo> meta;
    QList<std::shared_ptr<RouterVo>> parent;
};