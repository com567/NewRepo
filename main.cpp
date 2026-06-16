#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Service/MenuService.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile file(":/Resources/qss/style.css");
    if (!file.open(QFile::ReadOnly)) {
        app.setStyleSheet(file.readAll());
    }

    MainWindow window;
    MenuService::instance()->GetRouters();
    //auto menuService = MenuService::instance()->GetMenuTree();
    window.showMaximized();
    return app.exec();
}
