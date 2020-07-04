#ifndef BASE_H
#define BASE_H

#include "building.h"

class Base : public Building
{
public:
    Base(Player* ownedBy, GridSquare* createPos);
    ~Base();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // BASE_H
