#ifndef DISTANCE_H
#define DISTANCE_H

#include "gridsquare.h"

class Distance
{
public:
    Distance();
    static double pointDistance(GridSquare* pos1, GridSquare* pos2);
};

#endif // DISTANCE_H
