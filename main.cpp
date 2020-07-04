#include "mainwindow.h"

#include <QApplication>
#include <cstdlib>
#include <ctime>

MainWindow* w = nullptr;

int main(int argc, char *argv[]) {
    srand(time(0));

    QApplication a(argc, argv);
    w = new MainWindow();
    w->init();
    w->show();
    return a.exec();
}
