#include "ai.h"
#include "mainwindow.h"
#include "player.h"
#include "Units/worker.h"
#include "queuebuilding.h"
#include "queueunit.h"

#include <cmath>

extern MainWindow* w;

AI::AI(Player* plyr) {
    player = plyr;

    resDemand = ResourceDemand(player);

    QVector <AIVision*> newRow;

    for(int i = 0; i < w->bah->getGridX(); i++) {
        newRow.clear();
        for(int j = 0; j < w->bah->getGridY(); j++) {
            newRow.push_back(new AIVision(w->bah->getSquare(i, j)));
        }
        vision.push_back(newRow);
    }

    invasion = false;
}

AI::~AI() {
    for(int i = 0; i < w->bah->getGridX(); i++) {
        for(int j = 0; j < w->bah->getGridY(); j++)
            delete vision[i][j];
    }
}

void AI::resourceSearch() { //checks which resource is needed, acts accordingly
    GridSquare* resPos = nullptr;
    Worker* tmp = nullptr;
    char res = 'n';
    double maxDemand;


    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType()=='w' && unit->getMovesLeft() != 0) {
            this->updateResDemand();

            tmp = (Worker*) unit;
            if(!tmp->getQueueItem()) {
                maxDemand = resDemand.getGoldDemand();
                res = 'g';
                if(resDemand.getWoodDemand() > maxDemand) {
                    maxDemand = resDemand.getWoodDemand();
                    res = 'w';
                }
                else if(resDemand.getFoodDemand() > maxDemand) {
                    maxDemand = resDemand.getFoodDemand();
                    res = 'f';
                }
                else if(resDemand.getIronDemand() > maxDemand) {
                    maxDemand = resDemand.getIronDemand();
                    res = 'i';
                }


                resPos = this->resDecision(unit, res);
                if(resPos) {
                    unit->moveTo(resPos);
                    if(resPos == unit->getPosition())
                        this->makeResBuilding(unit);
                }
            }
        }
    }
    if(!resPos) {
        this->fortPlacement(res);
    }
}

void AI::updateResDemand() {
    //qDebug() << "updating: f: " << resDemand.getFoodDemand() << " w: " << resDemand.getWoodDemand() << " i: " << resDemand.getIronDemand() << " g: " << resDemand.getGoldDemand();
    resDemand.updateFoodDemand();
    resDemand.updateWoodDemand();
    resDemand.updateIronDemand();
    resDemand.updateGoldDemand();
    //qDebug() << "updated: f: " << resDemand.getFoodDemand() << " w: " << resDemand.getWoodDemand() << " i: " << resDemand.getIronDemand() << " g: " << resDemand.getGoldDemand();
}


GridSquare* AI::resDecision(Unit* worker, char res) {
    GridSquare* retSquare = nullptr;
    double distance;
    double locRatio = 0;
    double ratioAD = 0;

    for(int i = 0; i < vision.size(); i++) {
        for(int j = 0; j < vision[i].size(); j++) {
            if(vision[i][j]->getResource()->getAmount() != 0
                    && vision[i][j]->getResource()->getType() == res
                    && vision[i][j]->getSquare()->getOwner() == player
                    && !vision[i][j]->getResource()->isExploited()
                    && !vision[i][j]->getSquare()->getBuilding()) {
                distance = Distance::pointDistance(worker->getPosition(), vision[i][j]->getSquare());
                locRatio = vision[i][j]->getResource()->getAmount()/distance;
                if(locRatio > ratioAD) {
                    ratioAD = locRatio;
                    retSquare = vision[i][j]->getSquare();
                }
            }
        }
    }
    return retSquare;
}

void AI::makeResBuilding(Unit* worker) {
    if(worker->getPosition()->getResource()->getAmount() != 0
            && !worker->getPosition()->getBuilding()) {
        switch(worker->getPosition()->getResource()->getType()) {
        case 'f': this->queueResBuilding(worker, 'f'); break;
        case 'w': this->queueResBuilding(worker, 'w'); break;
        case 'i': this->queueResBuilding(worker, 'i'); break;
        case 'g': this->queueResBuilding(worker, 'g'); break;
        }
    }
}

void AI::queueResBuilding(Unit* worker, char res) {
    if(res == 'w') {
        new QueueBuilding('w', (Worker*)worker);
        qDebug() << "AI - Woodcamp queued";
    }
    else {
        if(res == 'f') {
            new QueueBuilding('f', (Worker*)worker);
            qDebug() << "AI - Farm queued";
        }
        else if(res == 'i' || res == 'g') {
            new QueueBuilding('m', (Worker*)worker);
            qDebug() << "AI - Mine queued";
        }
    }
}

void AI::unitRecruiter() {
    int unusedResCount = 0;
    int workerCount = 0;
    Building* base = nullptr;

    for(int i = 0; i < player->getOwnedBuildings().size(); i++) {
        if(player->getOwnedBuildings().at(i)->getType() == 'b') {
            base = player->getOwnedBuildings().at(i);
            i = player->getOwnedBuildings().size();
        }
    }

    if(player->getStockpile().getFood() >= 1 && !base->getQueueItem() && !base->getPosition()->getUnit()) {
        unusedResCount = this->countUnusedRes();

        for(Unit* unit : player->getOwnedUnits()) {
            if(unit->getType() == 'w')
                workerCount++;
        }

        if((unusedResCount/workerCount) > 5 || workerCount == 0) {
            new QueueUnit('w', base);
            qDebug() << "AI - Worker queued";
        }
    }
    this->buildArmy();
}

int AI::countUnusedRes() {
    int unusedResCount = 0;
    Worker* tmp = nullptr;

    for(int i = 0; i < w->bah->getGridX(); i++)
        for(int j = 0; j < w->bah->getGridY(); j++){
            if(!vision[i][j]->getResource()->isExploited()
                    && !vision[i][j]->getResource()->isDisabled()
                    && vision[i][j]->getSquare()->getOwner() == player
                    && vision[i][j]->getResource()->getType() != 'n') { //can be improved
                if(!vision[i][j]->getSquare()->getUnit()) { //if has no unit
                    unusedResCount++;
                } else { //else checks if the unit is worker
                    if(vision[i][j]->getSquare()->getUnit()->getType() == 'w') { // if the unit is worker check queue
                        tmp = (Worker*)vision[i][j]->getSquare()->getUnit();
                        if(!tmp->getQueueItem()) //if queue is empty, res is still unused
                            unusedResCount++;
                    }
                    else unusedResCount++;
                }
            }
        }
    return unusedResCount;
}

void AI::buildArmy() { //tries to keep the army ratio 1:1:1
    int archerCount = 0;
    int knightCount = 0;
    int pikemanCount = 0;

    for(Unit* unit : player->getOwnedUnits()) {
        switch(unit->getType()) {
        case 'a': archerCount++; break;
        case 'k': knightCount++; break;
        case 'p': pikemanCount++; break;
        }
    }

    for(Building* building : player->getOwnedBuildings()) {
        if(building->getType() == 'b' || building->getType() == 'r') {
            if(!building->getQueueItem() && !building->getPosition()->getUnit()) {
                if(archerCount <= pikemanCount && archerCount <= knightCount
                        && player->getStockpile().getFood() >= 1 && player->getStockpile().getWood() >= 1) {
                    new QueueUnit('a', building);
                    qDebug() << "AI - Archer queued";
                }
                else if(pikemanCount <= archerCount && pikemanCount <= knightCount
                        && player->getStockpile().getFood() >= 1 && player->getStockpile().getWood() >= 1) {
                    new QueueUnit('p', building);
                    qDebug() << "AI - Pikeman queued";
                }
                else if(knightCount <= archerCount && knightCount <= pikemanCount
                        && player->getStockpile().getFood() >= 1 && player->getStockpile().getIron() >= 1) {
                    new QueueUnit('k', building);
                    qDebug() << "AI - Knight queued";
                }
            }
        }
    }
}

void AI::fortPlacement(char res) {
    GridSquare* fortPos = nullptr;
    Worker* worker = nullptr;
    Worker* closestWorker = nullptr;
    double distance = 0;
    double minDistance = 1000;

    if(player->getStockpile().getWood() >= 5
            && player->getStockpile().getIron() >= 3
            && player->getStockpile().getGold() >= 2) {
        for(int i = 0; i < w->bah->getGridX(); i++) {
            for(int j = 0; j < w->bah->getGridY(); j++){
                if(!vision[i][j]->getSquare()->getOwner()
                        && vision[i][j]->isResVisible()
                        && vision[i][j]->getResource()->getType() == res) { //doesn't belong to anyone + knows resource
                    fortPos = this->searchForFortSpot(vision[i][j]->getSquare());
                    if(fortPos) { //found a square for fort
                        for(int i = 0; i < player->getOwnedUnits().size(); i++) {
                            if(player->getOwnedUnits().at(i)->getType() == 'w') { //found a worker
                                worker = (Worker*) player->getOwnedUnits().at(i);
                                if(!worker->getQueueItem()) { //is free
                                    distance = Distance::pointDistance(worker->getPosition(), fortPos);
                                    if(distance < minDistance) {
                                        minDistance = distance;
                                        closestWorker = worker;
                                    }
                                }
                            }
                        }
                        if(closestWorker) {
                            closestWorker->moveTo(fortPos);
                            if(closestWorker->getPosition() == fortPos) {
                                new QueueBuilding('r', closestWorker);
                                qDebug() << "AI - Fort queued";
                            }
                        }
                    }
                }
            }
        }
    }
}

GridSquare* AI::searchForFortSpot(GridSquare* resPos) {
    int fortAoI = 2;
    int locX = resPos->getX()/SQUARESIZE;
    int locY = resPos->getY()/SQUARESIZE;
    GridSquare* appropriateSquare = nullptr;

    for(int i = (0 - fortAoI); i <= fortAoI; i++) {
        if(locX+i < w->bah->getGridX() && locX+i >= 0) {
            for(int j = (0 - fortAoI); j < fortAoI+1; j++) {
                if(locY+j < w->bah->getGridY() && locY+j >= 0) {
                    if(vision[locX+i][locY+j]->getResource()->getAmount() == 0
                            && !vision[locX+i][locY+j]->getSquare()->getUnit()) //first cycle - no res
                        appropriateSquare = vision[locX+i][locY+j]->getSquare();
                }
            }
        }
    }

    if(!appropriateSquare) { //no app square
        for(int i = (0 - fortAoI); i <= fortAoI; i++) {
            if(locX+i < w->bah->getGridX() && locX+i >= 0) {
                for(int j = (0 - fortAoI); j < fortAoI+1; j++) {
                    if(locY+j < w->bah->getGridY() && locY+j >= 0) {
                        if(vision[locX+i][locY+j]->getResource()->getAmount() == 1
                                && vision[locX+i][locY+j]->getResource()->getType() != 'g'
                                && !vision[locX+i][locY+j]->getSquare()->getUnit()) //second cycle - amount 1, not gold
                            appropriateSquare = vision[locX+i][locY+j]->getSquare();
                    }
                }
            }
        }
    }

    return appropriateSquare;
}

void AI::armyMovement() {
    if(!(this->checkForEnemies())) {
        this->moveUnits();
    }
}

bool AI::checkForEnemies() {
    bool enemiesFound = false;
    Unit* chosenUnit = nullptr;
    Building* chosenBuilding = nullptr;
    double unitDistance = 1000;
    double buildingDistance = 1000;
    double distance = 0;

    for(Unit* unit : player->getOwnedUnits()) {
        for(int i = 0; i < w->bah->getGridX(); i++) {
            for(int j = 0; j < w->bah->getGridY(); j++) {
                if(vision[i][j]->isSqrVisible()) {
                    if(vision[i][j]->getSquare()->getUnit()) { //has a unit
                        if(vision[i][j]->getSquare()->getUnit()->getOwner() != player) { //enemy unit
                            distance = Distance::pointDistance(vision[i][j]->getSquare(), unit->getPosition());
                            if(distance < unitDistance) {
                                unitDistance = distance;
                                chosenUnit = vision[i][j]->getSquare()->getUnit();
                            }
                        }
                    }
                    else if(vision[i][j]->getSquare()->getBuilding()) { //or has building
                        if(vision[i][j]->getSquare()->getBuilding()->getOwner() != player) { //enemy building
                            if(!vision[i][j]->getSquare()->getBuilding()->getType() != 'b' || invasion) { //only attack base or fort if invasion is on
                                distance = Distance::pointDistance(vision[i][j]->getSquare(), unit->getPosition());
                                if(distance < buildingDistance) {
                                    buildingDistance = distance;
                                    chosenBuilding = vision[i][j]->getSquare()->getBuilding();
                                }
                            }
                        }
                    }
                }
            }
        }
        if(unitDistance > buildingDistance)
            chosenUnit = nullptr;
        else
            chosenBuilding = nullptr;
    }

    Unit* counterUnit = nullptr;

    if(chosenUnit) {
        enemiesFound = true;
        counterUnit = this->bestUnitForAttack(chosenUnit);
        if(counterUnit) {
            counterUnit->attackUnitAI(chosenUnit);
        }
    }
    else if(chosenBuilding) {
        enemiesFound = true;
        counterUnit = this->bestUnitForAttack(chosenBuilding);
        if(counterUnit) {
            counterUnit->attackBuildingAI(chosenBuilding);
        }
    }

    return enemiesFound;
}

Unit* AI::bestUnitForAttack(Unit* enemy) {
    double distance;
    double score = 0;
    double minScore = 1000;
    Unit* chosenUnit = nullptr;
    char enemyType = enemy->getType();
    char unitType;

    for(Unit* unit : player->getOwnedUnits()) {
        unitType = unit->getType();

        if(unitType != 'w' && unit->getMovesLeft() >=1) {
             distance = Distance::pointDistance(unit->getPosition(), enemy->getPosition());

            if(enemyType == 'w') { //attacking worker
                if(distance < minScore) {
                    minScore = distance;
                    chosenUnit = unit;
                }
            }
            else if(enemyType == 'a') { //attacking archer
                if(unitType == 'k')
                    score = distance/1.5;
                else if(unitType == 'a')
                    score = distance;
                else score = distance/0.5;

                if(score < minScore) {
                    minScore = score;
                    chosenUnit = unit;
                }
            }
            else if(enemyType == 'k') { //attacking knight
                if(unitType == 'p')
                    score = distance/1.5;
                else if(unitType == 'k')
                    score = distance;
                else score = distance/0.5;

                if(score < minScore) {
                    minScore = score;
                    chosenUnit = unit;
                }
            }
            else if(enemyType == 'p') { //attacking pike
                if(unitType == 'a')
                    score = distance/1.5;
                else if(unitType == 'p')
                    score = distance;
                else score = distance/0.5;

                if(score < minScore) {
                    minScore = score;
                    chosenUnit = unit;
                }
            }
        }
    }
    return chosenUnit;
}

Unit* AI::bestUnitForAttack(Building* enemy) {
    double distance = 0;
    double minDistance = 1000;
    Unit* chosenUnit = nullptr;
    char unitType;

    for(Unit* unit : player->getOwnedUnits()) {
        unitType = unit->getType();

        if(unitType != 'w' && unit->getMovesLeft() >=1) {
            if(abs(unit->getPosition()->getX()/SQUARESIZE - enemy->getPosition()->getX()/SQUARESIZE) >
                    abs(unit->getPosition()->getY()/SQUARESIZE - enemy->getPosition()->getY()/SQUARESIZE)) {
                distance = abs(unit->getPosition()->getX()/SQUARESIZE - enemy->getPosition()->getX()/SQUARESIZE);
            }
            else {
                distance = abs(unit->getPosition()->getY()/SQUARESIZE - enemy->getPosition()->getY()/SQUARESIZE);
            }

            if(distance < minDistance) {
                minDistance = distance;
                chosenUnit = unit;
            }
        }
    }
    return chosenUnit;
}

void AI::moveUnits() { //if can't find enemies
    GridSquare* pos = nullptr;

    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType() != 'w') {
            if((!unit->getPosition()->getResource()->isExploited()
                && unit->getPosition()->getResource()->getType() != 'n'
                && unit->getPosition()->getOwner() == player)) { //not exploited res
                //then has to move
                pos = findUnitsChillSquare(unit);
                if(pos) {
                    unit->moveTo(pos);
                }
            }
            else if(unit->getPosition()->getBuilding()) {
                if(unit->getPosition()->getBuilding()->getType() == 'b'
                        || unit->getPosition()->getBuilding()->getType() == 'r') { // on fort or base
                    //then has to move
                    pos = findUnitsChillSquare(unit);
                    if(pos) {
                        unit->moveTo(pos);
                    }
                }
            }
        }
    }
}

GridSquare* AI::findUnitsChillSquare(Unit* unit) {
    GridSquare* pos = nullptr;
    double minDistance = 1000;
    double distance = 0;

    for(int i = 0; i < w->bah->getGridX(); i++) {
        for(int j = 0; j < w->bah->getGridY(); j++){
            if(vision[i][j]->isSqrVisible() //sqr visible
                    && (vision[i][j]->getResource()->getType() == 'n' //empty res
                        || vision[i][j]->getResource()->isExploited()) //or is exploited
                    && !vision[i][j]->getResource()->isDisabled() //and no disabled res(either base or fort)
                    && !vision[i][j]->getSquare()->getUnit()) { //and no units present
                distance = Distance::pointDistance(vision[i][j]->getSquare(), unit->getPosition());
                if(distance < minDistance) {
                    pos = vision[i][j]->getSquare();
                    minDistance = distance;
                }
            }
        }
    }

    return pos;
}

void AI::considerInvasion() {
    int soldierCount = 0;

    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType() != 'w') { //counts soldiers - units that aren't workers
            soldierCount++;
        }
    }
    if(soldierCount >= 5) {
        invasion = true;
    }
    else
        invasion = false;
}

void AI::doInvasion() {
    Building* closestBase = nullptr;
    Building* playerBase = nullptr;
    double minDistance = 1000;
    double distance = 0;

    for(Building* building : player->getOwnedBuildings()) {
        if(building->getType() == 'b')
            playerBase = building;
    }

    if(playerBase) {
        for(int i = 0; i < w->bah->getGridX(); i++) {
            for(int j = 0; j < w->bah->getGridY(); j++) {
                if(vision[i][j]->getSquare()->getBuilding()) { //has building
                    if(vision[i][j]->getSquare()->getBuilding()->getType() == 'b'
                            && vision[i][j]->getSquare()->getBuilding()->getOwner() != player) { //enemy base
                        distance = Distance::pointDistance(vision[i][j]->getSquare(), playerBase->getPosition());
                        if(distance < minDistance) {
                            closestBase = vision[i][j]->getSquare()->getBuilding();
                            minDistance = distance;
                        }
                    }
                }
            }
        }
        if(closestBase) {
            this->moveUnitsTowards(closestBase);
        }
    }
}

void AI::moveUnitsTowards(Building* base) {
    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType() != 'w') { //moves soldiers
            unit->moveTo(base->getPosition());
        }
    }
}
