#include "distance.h"

Distance::Distance() { }

double Distance::pointDistance(GridSquare *pos1, GridSquare *pos2) {
    double distance = 0;
    if(abs(pos1->getX()/SQUARESIZE - pos2->getX()/SQUARESIZE) >
            abs(pos1->getY()/SQUARESIZE - pos2->getY()/SQUARESIZE)) {
        distance = abs(pos1->getX()/SQUARESIZE - pos2->getX()/SQUARESIZE);
    }
    else {
        distance = abs(pos1->getY()/SQUARESIZE - pos2->getY()/SQUARESIZE);
    }
    return distance;
}
