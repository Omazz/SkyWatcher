#include "GUI/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon("../Recources/SkyWatcherIcon.ico"));
    w.show();

    return a.exec();
}
