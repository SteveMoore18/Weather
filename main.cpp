#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    a.setWindowIcon(QIcon(":/icons/icons/AppIcon/app.ico"));
    return a.exec();
}
