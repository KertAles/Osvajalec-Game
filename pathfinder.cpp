#include "mainwindow.h"
#include "pathfinder.h"

#include <math.h>

extern MainWindow* w;

Pathfinder::Pathfinder() {

}

QList<GridSquare*> Pathfinder::findPath(Unit* unit, GridSquare* moveTo) {
    float x1 = unit->getPosition()->getX()/SQUARESIZE;
    float x2 = moveTo->getX()/SQUARESIZE;
    float y1 = unit->getPosition()->getY()/SQUARESIZE;
    float y2 = moveTo->getY()/SQUARESIZE;

    QList<GridSquare*> path;

    float xStep = (y1-y2)/(x1-x2); //koeficient
}
