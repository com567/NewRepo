#pragma once
#include "Domain/Vo/MetaVo.hpp"
#include <QString>
#include <QList>

//前端路由格式
struct RouterVo {
	QString name;
    QString path;
    // 路由重定向地址
    QString rdeirct;
    QString component;
    bool hidden;
    //路由元信息
    std::shared_ptr<MetaVo> meta;
    //子路由列表
    QList<std::shared_ptr<RouterVo>> children;
};