#ifndef WOODCAMP_H
#define WOODCAMP_H

#include "building.h"

class Woodcamp : public Building
{
public:
    Woodcamp(Player* ownedBy, GridSquare* createPos);
    ~Woodcamp();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // WOODCAMP_H
