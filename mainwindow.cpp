#include "mainwindow.h"
#include "gridsquare.h"
#include "victoryscreen.h"

#include <QRect>
#include <QMouseEvent>
#include <QDebug>

extern MainWindow* w;

MainWindow::MainWindow(QWidget *parent) : QGraphicsView(parent) {
    setFixedWidth(1280);
    setFixedHeight(720);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(true);

    this->setWindowTitle("OsvajalecGame");

    bah = new Game();
    menu = new Menu();
    selection = new SelectionScreen();
    victory = new VictoryScreen();
}

MainWindow::~MainWindow() {
    delete bah;
    delete menu;
    delete selection;
    delete victory;
}

void MainWindow::closeEvent(QCloseEvent *event) {
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    bah->updateCurrentMousePos(event->pos());
}

void MainWindow::init() {
    menu->init();
    w->setScene(menu);
}
