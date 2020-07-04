#ifndef PIKEMAN_H
#define PIKEMAN_H

#include "unit.h"

class Pikeman : public Unit
{
public:
    Pikeman(Player* ownedBy, GridSquare* createPos);
    ~Pikeman();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // PIKEMAN_H
