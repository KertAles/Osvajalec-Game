#include "maprevealer.h"
#include "ai.h"

#include <QDebug>

extern MainWindow* w;

MapRevealer::MapRevealer()
{

}

void MapRevealer::uncoverMap() {
    int x = w->bah->getGridX();
    int y = w->bah->getGridY();

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            w->bah->grid[i][j]->setFoW(false);
}

void MapRevealer::revealMap(Player *player) {
    int x = w->bah->getGridX();
    int y = w->bah->getGridY();
    int locX = 0;
    int locY = 0;

    bool mode = true;
    if(w->bah->mode == 't') //test mode, so you can see what's going on with the AI
        mode = false;

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            w->bah->grid[i][j]->setFoW(mode);

    QList<Unit*> units = player->getOwnedUnits();
    QList<Building*> buildings = player->getOwnedBuildings();

    for(Unit* unit: units) {
        locX = unit->getPosition()->getX()/SQUARESIZE;
        locY = unit->getPosition()->getY()/SQUARESIZE;
        for(int i = (0 - unit->getLoS()); i <= unit->getLoS(); i++) {
            if(locX+i < x && locX+i >= 0) {
                for(int j = (0 - unit->getLoS()); j < unit->getLoS()+1; j++) {
                    if(locY+j < y && locY+j >= 0) {
                        w->bah->grid[locX+i][locY+j]->setFoW(false);
                    }
                }
            }
        }
    }

    for(Building* building: buildings) {
        locX = building->getPosition()->getX()/SQUARESIZE;
        locY = building->getPosition()->getY()/SQUARESIZE;
        for(int i = (0 - building->getLoS()); i <= building->getLoS(); i++) {
            if(locX+i < x && locX+i >= 0) {
                for(int j = (0 - building->getLoS()); j < building->getLoS()+1; j++) {
                    if(locY+j < y && locY+j >= 0) {
                        w->bah->grid[locX+i][locY+j]->setFoW(false);
                    }
                }
            }
        }
    }
}


void MapRevealer::revealMapAI(Player *player) {
    int x = w->bah->getGridX();
    int y = w->bah->getGridY();
    int locX = 0;
    int locY = 0;

    for(int i = 0; i < x; i++)
        for(int j = 0; j < y; j++)
            player->getAI()->getAIVision(i,j)->setSqrVisible(false);

    QList<Unit*> units = player->getOwnedUnits();
    QList<Building*> buildings = player->getOwnedBuildings();

    for(Unit* unit: units) {
        locX = unit->getPosition()->getX()/SQUARESIZE;
        locY = unit->getPosition()->getY()/SQUARESIZE;
        for(int i = (0 - unit->getLoS()); i <= unit->getLoS(); i++) {
            if(locX+i < x && locX+i >= 0) {
                for(int j = (0 - unit->getLoS()); j < unit->getLoS()+1; j++) {
                    if(locY+j < y && locY+j >= 0) {
                        player->getAI()->getAIVision(locX+i,locY+j)->setSqrVisible(true);
                    }
                }
            }
        }
    }

    for(Building* building: buildings) {
        locX = building->getPosition()->getX()/SQUARESIZE;
        locY = building->getPosition()->getY()/SQUARESIZE;
        for(int i = (0 - building->getLoS()); i <= building->getLoS(); i++) {
            if(locX+i < x && locX+i >= 0) {
                for(int j = (0 - building->getLoS()); j < building->getLoS()+1; j++) {
                    if(locY+j < y && locY+j >= 0) {
                        player->getAI()->getAIVision(locX+i,locY+j)->setSqrVisible(true);
                    }
                }
            }
        }
    }
}
