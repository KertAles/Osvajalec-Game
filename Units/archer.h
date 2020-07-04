#ifndef ARCHER_H
#define ARCHER_H

#include "unit.h"

class Archer : public Unit
{
public:
    Archer(Player* ownedBy, GridSquare* createPos);
    ~Archer();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // ARCHER_H
