#include "MenuMgrPage.h"
#include "Service/MenuService.h"
#include <QStandardItem>

MenuMgrPage::MenuMgrPage(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MenuMgrPageClass())
	,m_model(new QStandardItemModel(this))
{
	ui->setupUi(this);
	ui->MenuView->setModel(m_model);
}

MenuMgrPage::~MenuMgrPage()
{
	delete ui;
}


QList<QStandardItem*>GetMenuItem(const std::shared_ptr<Menu>& menu) {
	QList<QStandardItem*> itemlist;
	itemlist.emplaceBack(new QStandardItem(menu->function_id));
	itemlist.emplaceBack(new QStandardItem(menu->function_name));
	itemlist.emplaceBack(new QStandardItem(menu->perms));
	itemlist.emplaceBack(new QStandardItem(menu->parent_id));
	itemlist.emplaceBack(new QStandardItem(menu->menu_type));
	itemlist.emplaceBack(new QStandardItem(menu->is_frame));
	itemlist.emplaceBack(new QStandardItem(menu->is_visible));
	itemlist.emplaceBack(new QStandardItem(menu->is_active));
	itemlist.emplaceBack(new QStandardItem(menu->path));

	return itemlist;

}

void MenuMgrPage::on_searchBtn_clicked()
{
	auto menuService = MenuService::instance();
	auto menuList = menuService->GetMenuTree();
	for (auto& menu : menuList) {
		auto item= GetMenuItem(menu);
		m_model->appendRow(item);
	}
}

void MenuMgrPage::on_ResetBtn_clicked()
{
	ui->searchbox->clear();
	ui->comboBox->setCurrentIndex(0);
}


