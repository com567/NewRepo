#pragma once
#include <QList>

struct Menu {
	quint32 function_id;
	QString function_name;
	quint16 parent_id;
	quint8 order_num;
	QString path;
	QString component;
	quint8 is_frame;
	QString menu_type;
	quint8 is_visible;
	quint8 is_active;
	QString perms;

	QList<std::shared_ptr<Menu>>children;
};