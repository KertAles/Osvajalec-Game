#ifndef MINE_H
#define MINE_H

#include "building.h"

class Mine : public Building
{
public:
    Mine(Player* ownedBy, GridSquare* createPos);
    ~Mine();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // MINE_H
