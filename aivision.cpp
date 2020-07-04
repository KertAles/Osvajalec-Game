#include "aivision.h"

AIVision::AIVision(GridSquare* sqr) {
    square = sqr;
    sqrVisible = false;

    resource = square->getResource();
    resVisible = false;

    //dangerLevel = 0;
}

