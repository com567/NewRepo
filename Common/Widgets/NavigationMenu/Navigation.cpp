#include "Common/Constants/UserConstant.hpp"
#include "Navigation.h"
#include <QDesktopServices>
#include <QHeaderView>
#include <QUrl>
Navigation::Navigation(QWidget *parent)
	: QTreeView(parent)
	,m_model(new QStandardItemModel(this))
{
	setAttribute(Qt::WA_StyledBackground);
	setModel(m_model);
    setAnimated(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_model->setHorizontalHeaderLabels(QStringList() << "道 观 管 理 系 统");
    QFont headerFont;// 保证表头可见并设置固定高度
    headerFont.setPointSize(18); if (header()) {
        m_model->setHeaderData(0, Qt::Horizontal, headerFont, Qt::FontRole);    header()->setFixedHeight(80);
        m_model->setHeaderData(0, Qt::Horizontal, QBrush(QColor(55, 187, 240)), Qt::ForegroundRole);    //文字居中
        header()->setDefaultAlignment(Qt::AlignCenter);
    }
    // setUniformRowHeights(true); // 优化并强制统一行高

    connect(this, &QTreeView::clicked, this, &Navigation::onItemClicked);
}

Navigation::~Navigation()
{}

template<typename T>
void recursionFn(const QList<std::shared_ptr<RouterVo>>& routers, T* parentItem) {
    if (routers.isEmpty()) { return; }
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

    for (auto& router : routers) {
        if (router->hidden) {
           continue;
        }
        auto item = new QStandardItem(router->name);
        item= makeItem(router->meta->title);
        item->setData(QVariant::fromValue(router),Qt::UserRole );
        /*if (router->rdeirct == UserConstant::NO_REDIRECT) {
            item->setSelectable(false);
        }*/

        recursionFn(router->children, item);
        parentItem->appendRow(item);
    }
}

void Navigation::setRouterVo(const QList<std::shared_ptr<RouterVo>>&routers)
{
    if (routers.isEmpty()) {
        return;
    }
    

    recursionFn(routers, m_model);
}


// 点击处理：优先判断 meta.link 是否为外部链接，外链用系统浏览器打开；否则发出内部跳转信号
void Navigation::onItemClicked(const QModelIndex& index)
{
    if (!index.isValid()) return;
    QStandardItem* item = m_model->itemFromIndex(index);
    if (!item) return;

    QString link = item->data(Qt::UserRole + 1).toString();
    if (link.startsWith("http://", Qt::CaseInsensitive) || link.startsWith("https://", Qt::CaseInsensitive)) {
        QDesktopServices::openUrl(QUrl(link));
        return;
    }

    // 非外链，发出内部路由跳转（link 可能以 '/' 开头，若为空可用 item 文本或其它 data）
    if (!link.isEmpty()) {
        emit sigNavigate(link);
    }
    else {
        // 如果没有 link，尝试用 item 存的 RouterVo（若已注册并可取出）
        QVariant v = item->data(Qt::UserRole);
        if (v.isValid()) {
            auto routerPtr = v.value<std::shared_ptr<RouterVo>>();
            if (routerPtr) {
                // 使用 router->path 或 meta->link 作为内部路由
                QString path = routerPtr->meta ? routerPtr->meta->link : routerPtr->path;
                if (!path.isEmpty()) emit sigNavigate(path);
            }
        }
    }
}



