#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "gridsquare.h"
#include "unit.h"

#include <QList>

class Pathfinder
{
public:
    Pathfinder();

    static QList<GridSquare*> findPath(Unit* unit, GridSquare* moveTo);
signals:

public slots:
};

#endif // PATHFINDER_H
