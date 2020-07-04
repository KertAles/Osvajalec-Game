#ifndef FORT_H
#define FORT_H

#include "building.h"

class Fort : public Building
{
public:
    Fort(Player* ownedBy, GridSquare* createPos);
    ~Fort();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:

public slots:
};

#endif // FORT_H
