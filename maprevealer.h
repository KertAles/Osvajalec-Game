#ifndef MAPREVEALER_H
#define MAPREVEALER_H

#include "mainwindow.h"
#include "player.h"

class Player;
class MainWindow;

class MapRevealer
{
public:
    MapRevealer();
    static void uncoverMap();
    static void revealMap(Player* player);
    static void revealMapAI(Player *player);
signals:

public slots:
};

#endif // MAPREVEALER_H
