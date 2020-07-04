#ifndef KNIGHT_H
#define KNIGHT_H

#include "unit.h"

class Knight : public Unit
{
public:
    Knight(Player* ownedBy, GridSquare* createPos);
    ~Knight();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // KNIGHT_H
