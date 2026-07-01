#pragma once

#include <QStyledItemDelegate>

class NavTreeDelegate  : public QStyledItemDelegate
{
	Q_OBJECT

public:
	NavTreeDelegate(QObject *parent);
	~NavTreeDelegate();
};

