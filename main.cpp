#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile file(":/Resources/qss/style.css");
    if (!file.open(QFile::ReadOnly)) {
        app.setStyleSheet(file.readAll());
    }

    MainWindow window;
    window.showMaximized();
    
    return app.exec();
}
