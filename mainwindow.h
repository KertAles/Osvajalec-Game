#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include "menu.h"
#include "selectionscreen.h"
#include "pathfinding/distance.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTime>
#include <QCoreApplication>

#define SQUARESIZE 70
#define UNITSIZE 30
#define BUILDINGSIZE 30
#define RESOURCESIZE 21
#define HPBARSIZE 400
#define HPBARHEIGHT 20

#define MAPCHECKOFFSET 2

class Game;
class VictoryScreen;

class MainWindow : public QGraphicsView
{
    Q_OBJECT

    void closeEvent(QCloseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public:
    Game* bah;
    Menu* menu;
    SelectionScreen* selection;
    VictoryScreen* victory;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
};

#endif // MAINWINDOW_H
