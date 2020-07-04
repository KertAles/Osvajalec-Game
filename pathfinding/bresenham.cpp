#include "mainwindow.h"
#include "bresenham.h"

#include <math.h>

extern MainWindow* w;

Bresenham::Bresenham()
{

}

QList<GridSquare*> Bresenham::findPath(Unit* unit, GridSquare* moveTo) {
    int x1 = unit->getPosition()->getX()/SQUARESIZE;
    int x2 = moveTo->getX()/SQUARESIZE;
    int y1 = unit->getPosition()->getY()/SQUARESIZE;
    int y2 = moveTo->getY()/SQUARESIZE;
    QList<GridSquare*> path;

    int dx = (x2 - x1);
    int dy;
    double k;
    bool back = true; //where the square will be added

    if(dx < 0) { //bresenham works left->right
        dx = abs(dx);

        x1 = x1 + x2; //switch points
        x2 = x1 - x2;
        x1 = x1 - x2;

        y1 = y1 + y2;
        y2 = y1 - y2;
        y1 = y1 - y2;

        back = false;
    }

    dy = (y2 - y1);

    if(dx == 0) { //vertical
        if(dy > 0) {
            for(int x = x1, y = y1; y <= y2; y++) {
                path.push_back(w->bah->getSquare(x,y));
            }
        }
        else {
            for(int x = x1, y = y1; y >= y2; y--) {
                path.push_back(w->bah->getSquare(x,y));
            }
        }
    }
    else {
        if(dy == 0) { //horizontal
            for(int x = x1, y = y1; x <= x2; x++) {
                if(back)
                    path.push_back(w->bah->getSquare(x,y));
                else
                    path.push_front(w->bah->getSquare(x,y));
            }
        }
        else {
            k = (double)dy/dx;
            if(abs(dy) <= dx) { //shallow
                double ySum = 0;
                for(int x = x1, y = y1; x <= x2; x++) {
                    if(dy > 0) { //falling
                        ySum += k;
                        if(ySum > 1) {
                            y++;
                            ySum -= 1;
                        }
                    }
                    else { //rising
                        ySum += k;
                        if(ySum < -1) {
                            y--;
                            ySum += 1;
                        }
                    }
                    if(back)
                        path.push_back(w->bah->getSquare(x,y));
                    else
                        path.push_front(w->bah->getSquare(x,y));
                }
            }
            else { //steep
                double xSum = 0;
                if(dy > 0) { //falling
                    for(int y = y1, x = x1; y <= y2; y++) {
                        xSum += 1.0/k;
                        if(xSum > 1) {
                            x++;
                            xSum -= 1;
                        }
                        if(back)
                            path.push_back(w->bah->getSquare(x,y));
                        else
                            path.push_front(w->bah->getSquare(x,y));
                    }
                }
                else { //rising
                    for(int y = y1, x = x1; y >= y2; y--) {
                        xSum += 1.0/k;
                        if(xSum < -1) {
                            x++;
                            xSum += 1;
                        }
                        if(back)
                            path.push_back(w->bah->getSquare(x,y));
                        else
                            path.push_front(w->bah->getSquare(x,y));
                    }
                }
            }
        }
    }
    if(path.size() != 0) {
        path.removeFirst(); //don't want to move to the current square
    }
    return path;
}

