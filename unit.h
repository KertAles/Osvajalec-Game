#ifndef UNIT_H
#define UNIT_H

#include "mainwindow.h"
#include "gridsquare.h"
#include "player.h"
#include "upkeep.h"

#include <QList>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Player;
class QueueBuilding;

class Unit : public QObject , public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
protected:
    QGraphicsPixmapItem* unitPix;
    QGraphicsEllipseItem* background;

    GridSquare* position;

    bool moving;

    int maxHp;
    int hp;
    int attack;
    int defense;
    int range;
    int los; //line of sight
    Upkeep upkeep;

    double movesLeft;
    double maxMoves;

    Player* owner;
    char type;
public:
    Unit();

    void init();

    Player* getOwner();
    GridSquare* getPosition();
    int getLoS();
    int getMaxHp() { return maxHp; }
    int getHp() { return hp; }
    double getMovesLeft() { return movesLeft; }
    double getMaxMoves() { return maxMoves; }
    char getType() { return type; }
    Upkeep getUpkeep() { return upkeep; }
    bool isMoving() { return moving; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void move(GridSquare* newPos); //en premik
    void moveTo(GridSquare* newPos); //celotna pot, kombinirano s pathfinder
    void killMoves() { movesLeft = 0; }
    void resetMoves() { movesLeft = maxMoves; }

    bool attackUnit(Unit* enemy);
    void attackUnitAI(Unit* enemy);
    bool attackBuilding(Building* enemy);
    void attackBuildingAI(Building* enemy);
    bool inRange(Unit* enemy);
    bool inRange(Building* enemy);
    bool inRange(GridSquare* pos);

    void attacked(int dmg, Unit* opponent);
    int biteBack(Unit* opponent);
signals:

public slots:
};

#endif // UNIT_H
