#ifndef BRESENHAM_H
#define BRESENHAM_H

#include "gridsquare.h"

class Unit;

class Bresenham
{
public:
    Bresenham();
    static QList<GridSquare*> findPath(Unit* unit, GridSquare* newPos);
};

#endif // BRESENHAM_H
