#include "GUI/MainWindow.h"
#include "../PriFiles/LoadingScreen/AppLoadScreen.h"

#include <QApplication>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon("../Recources/SkyWatcherIcon.ico"));
    AppLoadScreen loadScreen(QPixmap("../Recources/LoadingScreen.jpg"));

    loadScreen.showLoadingScreen(1000, &w);
    w.show();

    return a.exec();
}
