#include "influencecalculator.h"
#include "mainwindow.h"
#include "building.h"
#include "player.h"

#include <cmath>

extern MainWindow* w;

InfluenceCalculator::InfluenceCalculator()
{ }

void InfluenceCalculator::calculateInfluence() {
    int x = w->bah->getGridX();
    int y = w->bah->getGridY();
    int locX = 0;
    int locY = 0;

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            w->bah->grid[i][j]->resetInfluence();

    QList<Player*> players = w->bah->getPlayers();

    for(Player* player : players) {
        QList<Building*> buildings = player->getOwnedBuildings();

        for(Building* building: buildings) {
            if(building->getType() == 'b' || building->getType() == 'r') {
                locX = building->getPosition()->getX()/SQUARESIZE;
                locY = building->getPosition()->getY()/SQUARESIZE;
                for(int i = (0 - building->getAoI()); i <= building->getAoI(); i++) {
                    if(locX+i < x && locX+i >= 0) {
                        for(int j = (0 - building->getAoI()); j < building->getAoI()+1; j++) {
                            if(locY+j < y && locY+j >= 0) {
                                InfluenceCalculator::calcSquareInfluence(w->bah->grid[locX+i][locY+j], building);
                            }
                        }
                    }
                }
            }
        }
    }
    InfluenceCalculator::updateOwners();
}

void InfluenceCalculator::calcSquareInfluence(GridSquare* square, Building* building) {
    double val = 20; //base value
    double distance;
    distance = sqrt(pow((square->getX()/SQUARESIZE - building->getPosition()->getX()/SQUARESIZE),2)
                    + pow((square->getY()/SQUARESIZE - building->getPosition()->getY()/SQUARESIZE), 2));

    if(distance != 0) {
        val = val/(pow(distance, 2));
    }

    square->setInfluence(building->getOwner(), val);
}

void InfluenceCalculator::updateOwners() {
    int x = w->bah->getGridX();
    int y = w->bah->getGridY();

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            w->bah->grid[i][j]->setOwner(w->bah->grid[i][j]->mostInfluentialPlayer());
}

void InfluenceCalculator::removePlayer(Player* player) {
    int x = w->bah->getGridX();
    int y = w->bah->getGridY();

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            w->bah->grid[i][j]->removePlayer(player);
}
