#ifndef FARM_H
#define FARM_H

#include "building.h"

class Farm : public Building
{
public:
    Farm(Player* ownedBy, GridSquare* createPos);
    ~Farm();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // FARM_H
