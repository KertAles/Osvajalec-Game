#ifndef BUILDING_H
#define BUILDING_H

#include "mainwindow.h"
#include "gridsquare.h"
#include "player.h"
#include "influencecalculator.h"

#include <QList>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class Player;
class QueueUnit;

class Building : public QGraphicsItemGroup
{
protected:
    QGraphicsPixmapItem* buildPix;
    QGraphicsEllipseItem* background;

    bool blocksMovement; //v bistvu isFort

    int maxHp;
    int hp;
    int defense;
    int los; //line of sight
    char type;
    int areaOfInfluence;

    Player* owner;
    GridSquare* position;
    QueueUnit* queueItem;
public:
    Building();

    void init();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool doesBlock();
    Player* getOwner();
    GridSquare* getPosition();
    int getLoS();
    int getAoI() { return areaOfInfluence; }
    int getHp() { return hp; }
    int getMaxHp() { return maxHp; }
    char getType() { return type; }
    int getDefense() { return defense; }
    void setOwner(Player* newOwner) { owner = newOwner; }
    void attacked(int atk);
    int biteBack();

    void setQueueItem(QueueUnit* newItem);
    void unsetQueueItem();
    void undoQueueItem();
    void deleteQueueItem();
    QueueUnit* getQueueItem();
signals:

public slots:
};

#endif // BUILDING_H
