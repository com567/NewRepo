#pragma once
#include <QMap>
#include <QWidget>
#include <QPointer>
#include "Home.h"
#include "ui_HomePage.h"


class PersonallnfoPage;

class NotifyTipManager;
QT_BEGIN_NAMESPACE
namespace Ui { class HomePageClass; };
QT_END_NAMESPACE

class HomePage : public QWidget
{
	Q_OBJECT

public:
	HomePage(QWidget *parent = nullptr);
	~HomePage();
	void AvatarChanged();
	void setCurrentPage(const QString& componect,const QString&title);

protected:
	void resizeEvent(QResizeEvent *event) override;
signals:
	void sig_quit_login();

public slots:
	//void onNavigate(const QString& path);
	void slot_cut_path(const QModelIndex& index);

private:
	Ui::HomePageClass *ui;
	//储存所有菜单
	QMap<QString,QPointer<QWidget>> m_pages;
	QPointer<PersonallnfoPage> m_personalInfoPage{};

	template<typename T>
	inline QWidget* addPage(const QString& title);

	QMenu* m_personalMenu{};
	void initPersonalMenu();
};

template<typename T>
	inline QWidget* HomePage::addPage(const QString& title) {
		auto it=m_pages.find(title);
		if (it != m_pages.end())return *it;
		auto personalPage = new T;
		m_pages.insert(title, personalPage);
		ui->Content->addWidget(personalPage);
		return personalPage;
	}