#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include "resource.h"
#include "unit.h"
#include "building.h"

#include <QGraphicsItem>

class Unit;
class Building;
class Influence;

class GridSquare : public QGraphicsPixmapItem
{
    int x;
    int y;
    char terrain;
    QPixmap terrainPixmap;
    Resource* resource;

    float costToMove;

    Player* owner;
    QList<Influence*> influence;
    bool fow;
public:
    Unit* unit;
    Building* building;

    GridSquare();
    GridSquare(int i, int j);
    ~GridSquare();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void resetInfluence();
    void removePlayer(Player* player);
    void setInfluence(Player* player, double infl);
    Player* mostInfluentialPlayer();

    int getX();
    int getY();
    char getTerrain();
    bool getFow() { return fow; }
    void setTerrain(char newTerrain);
    void setOwner(Player* player) { owner = player; }
    Player* getOwner() { return owner; }
    float getCostToMove();
    Unit* getUnit();
    void setUnit(Unit* newUnit);
    void unsetUnit();
    Building* getBuilding();
    void setBuilding(Building* newBuilding);
    void unsetBuilding();
    Resource* getResource();
    void setFoW(bool set);


    void updateTerrainPicture();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // GRIDSQUARE_H
