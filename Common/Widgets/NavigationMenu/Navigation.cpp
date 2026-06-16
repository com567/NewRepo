#include "Navigation.h"
#include <QHeaderView>
Navigation::Navigation(QWidget *parent)
	: QTreeView(parent)
	,m_model(new QStandardItemModel(this))
{
	setAttribute(Qt::WA_StyledBackground);
	setModel(m_model);
    setAnimated(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 保证表头可见并设置固定高度
    if (header()) {
        header()->setFixedHeight(80); 
        //文字居中
        header()->setDefaultAlignment(Qt::AlignCenter);
    }
    setUniformRowHeights(true); // 优化并强制统一行高
    interface();
}

Navigation::~Navigation()
{}


void Navigation::interface()
{
    m_model->setHorizontalHeaderLabels(QStringList() << "道 观 管 理 系 统");
    QFont headerFont;
    headerFont.setPointSize(18);
    m_model->setHeaderData(0, Qt::Horizontal, headerFont, Qt::FontRole);
    m_model->setHeaderData(0, Qt::Horizontal, QBrush(QColor(55, 187, 240)), Qt::ForegroundRole);
    // 项目样式：黑色 (0,0,0)，12号字体
    QFont itemFont;
    itemFont.setPointSize(12);
    QBrush itemBrush(QColor(0, 0, 0));
    constexpr int itemHeight = 40;

    auto makeItem = [&](const QString& text) -> QStandardItem* {
        QStandardItem* it = new QStandardItem(text);
        it->setFont(itemFont);
        it->setForeground(itemBrush);
        it->setSizeHint(QSize(0, itemHeight));
        return it;
        };

	auto item = makeItem("首页");
    m_model->appendRow(item);
    item = makeItem("管理");
	item->appendRow(makeItem("用户管理"));
    item->appendRow(makeItem("群组管理"));
	item->appendRow(makeItem("系统管理"));
    item->appendRow(makeItem("日志管理"));
    m_model->appendRow(item);

	item = makeItem("充值");
    m_model->appendRow(item);

    item = makeItem("帮助");
    m_model->appendRow(item);

    item = makeItem("设置");
    m_model->appendRow(item);
    
    item = makeItem("社区");
    item->appendRow(makeItem("论坛"));
    item->appendRow(makeItem("反馈"));
    m_model->appendRow(item);
}


