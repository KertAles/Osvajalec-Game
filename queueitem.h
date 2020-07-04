#ifndef QUEUEITEM_H
#define QUEUEITEM_H

#include "gridsquare.h"
#include "player.h"

class Player;

class QueueItem
{
protected:
    Player* owner;
    GridSquare* pos;

    int turnsLeft;
public:
    char type;

    QueueItem();

    char getType() { return type; }
    int getTurnsLeft() { return turnsLeft; }
    Player* getOwner() { return owner; }

    virtual void createItem() = 0;
    void countdown();
};

#endif // QUEUEITEM_H
