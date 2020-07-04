#include "mainwindow.h"
#include "game.h"
#include "mapcheck.h"
#include "maprevealer.h"
#include "victoryscreen.h"

#include "queueunit.h"
#include "queuebuilding.h"

#include "units\worker.h"
#include "units\pikeman.h"
#include "buildings\farm.h"
#include "buildings\base.h"
#include "UI/uitopbar.h"
#include "UI/uibottombar.h"

#include <QDebug>
#include <QList>
#include <math.h>
#include <QGraphicsSceneWheelEvent>

extern MainWindow* w;

Game::Game() {
    topBar = nullptr;
    bottomBar = nullptr;
    gridX = 0;
    gridY = 0;

    localPlayer = nullptr;
    activePlayer = nullptr;
    selectedUnit = nullptr;
    selectedBuilding = nullptr;
    unitOrderType = 'k';

    destroying = false;
    gameOver =  false;
}

Game::~Game() {
    destroying = true;
    if(topBar)
        delete topBar;
    if(bottomBar)
        delete bottomBar;

    for(int i = 0; i < queue.count(); i++) {
        if(queue.at(i))
            delete queue.at(i);
    }

    for(int i = 0; i < players.size(); i++) {
        if(players.at(i))
            delete players.at(i);
    }

    for(int i = 0; i < gridX; i++)
        for(int j = 0; j < gridY; j++)
            if(grid[i][j])
                delete grid[i][j];
}

void Game::gameLoop() {
    updatePosition();
    uiManager.update();
    if(!gameOver) {
        if(localPlayer)
            MapRevealer::revealMap(localPlayer);
    }
    this -> update();
}

int Game::getGridX()
{ return gridX; }

int Game::getGridY()
{ return gridY; }

void Game::updateCurrentMousePos(QPoint point) {
    currentMousePos = point;
}

void Game::updatePosition() {
    float speed = 7.0f;
    QPointF topPoint = w->mapToScene(20.0f,20.0f);
    QPointF bottomPoint(topPoint.x()+w->width()-40, topPoint.y()+w->height()-40);
    QRectF borderRect(topPoint,bottomPoint);
    QPointF mousePos = w->mapToScene(currentMousePos);
    QPointF centerPos = w->mapToScene(w->width()/2-1, w->height()/2-1);

    if(!borderRect.contains(mousePos)) //move viewport if cursor out of center rect
    {
        if(mousePos.x() < (borderRect.x()))  //left of rect
           { centerPos.setX(centerPos.x() - speed); }
        else if(mousePos.x() > (borderRect.x() + borderRect.width())) //right of rect
           { centerPos.setX(centerPos.x() + speed); }

        if(mousePos.y() < (borderRect.y())) //above rect
           { centerPos.setY(centerPos.y() - speed); }
        else if(mousePos.y() > (borderRect.y() + borderRect.height())) //below rect
           { centerPos.setY(centerPos.y() + speed); }
    }
    w->centerOn(centerPos);
}

void Game::updateTopBar() {
    topBar->updateResData(localPlayer);
}

void Game::init(QList<Player*> playerList, int sizeX, int sizeY, char moud) {
    gridX = sizeX;
    gridY = sizeY;

    mode = moud;

    localPlayer = nullptr;
    activePlayer = nullptr;
    selectedUnit = nullptr;
    selectedBuilding = nullptr;
    unitOrderType = 'm';

    this->setSceneRect(0.0f, 0.0f, gridX*SQUARESIZE, gridY*SQUARESIZE+225);

    players = playerList;
    localPlayer = players.first();
    localPlayer->setHuman(true);

    QVector <GridSquare*> newRow;

    for(int i = 0; i < gridX; i++) {
        newRow.clear();
        for(int j = 0; j < gridY; j++)
        {
            newRow.push_back(new GridSquare(i,j));
            this -> addItem(newRow.last());
            newRow.last() -> setPos(newRow.last() -> getX(), newRow.last() -> getY());
        }
        grid.push_back(newRow);
    }
    this->addItem(&uiManager);

    uiManager.setZValue(1.0f);

    topBar = new UITopBar;
    bottomBar = new UIBottomBar;

    topBar->init(w->width(), 50.0f);
    bottomBar->init(w->width(), 180.0f);

    uiManager.addComponent(topBar);
    uiManager.addComponent(bottomBar);

    generateTerrain(true);
    while(!checkMapValidity(players.size())) //This map ain't big enough for all of us...
        generateTerrain(false);

    gameLoopTimer.setInterval((1/60.0f)*1000.0f);
    this->connect(&gameLoopTimer, SIGNAL(timeout()), this, SLOT(gameLoop())); //Gejm..........loop
    gameLoopTimer.start();

    w->centerOn(localPlayer->getOwnedBuildings().first()->pos());

    for(Player* player: players) {
        player->initAI();
    }

    localPlayer->startTurn(); //start player cycle
}

void Game::generateTerrain(bool first) {
    for(int i = 0; i < gridX; i++)
        for(int j = 0; j < gridY; j++)
        {
            char decidedTerrain = 'w';
            decidedTerrain = decideTerrain(i,j);
            grid[i][j] -> setTerrain(decidedTerrain);

            grid[i][j] -> getResource() -> generateResource(grid[i][j]);
            if(first) {
                grid[i][j] -> getResource() -> addToScene();
                grid[i][j] -> getResource() -> hideResource();
            }
        }
}

char Game::decideTerrain(int i, int j) {
    char returnTerrain = 'n';
    int dice;
    if(i == 0 && j == 0) {
        dice = rand()%4;
        switch(dice) {
            case 0: returnTerrain = 'p'; break;
            case 1: returnTerrain = 'w'; break;
            case 2: returnTerrain = 'h'; break;
            case 3: returnTerrain = 'm'; break;
        }
    }
    else  {
        int countAdjacentTerrain[4];
        for(int i = 0; i < 4; i++)
            countAdjacentTerrain[i] = 0;

       if(i != 0) {
            switch(grid[i-1][j]->getTerrain()) {
                case 'p': countAdjacentTerrain[0]++; break;
                case 'w': countAdjacentTerrain[1]++; break;
                case 'h': countAdjacentTerrain[2]++; break;
                case 'm': countAdjacentTerrain[3]++; break;
            }
        }
        if(j != 0) {
            switch(grid[i][j-1]->getTerrain()) {
                case 'p': countAdjacentTerrain[0]++; break;
                case 'w': countAdjacentTerrain[1]++; break;
                case 'h': countAdjacentTerrain[2]++; break;
                case 'm': countAdjacentTerrain[3]++; break;
            }
        }

        if(j != 0 && i != 0) {
            switch(grid[i-1][j-1]->getTerrain()) {
                case 'p': countAdjacentTerrain[0]++; break;
                case 'w': countAdjacentTerrain[1]++; break;
                case 'h': countAdjacentTerrain[2]++; break;
                case 'm': countAdjacentTerrain[3]++; break;
            }
        }

        int terrainDecidingValues[4];
        for(int i = 0; i < 4; i++)
            terrainDecidingValues[i] = 0;
                                                                   //plains
        terrainDecidingValues[0] += pow(38, countAdjacentTerrain[0]);   //p
        terrainDecidingValues[1] += pow(35, countAdjacentTerrain[0]);   //w
        terrainDecidingValues[2] += pow(30, countAdjacentTerrain[0]);   //h
        terrainDecidingValues[3] += pow(0, countAdjacentTerrain[0]);    //m
                                                                  //woods
        terrainDecidingValues[0] += pow(35, countAdjacentTerrain[1]);   //p
        terrainDecidingValues[1] += pow(38, countAdjacentTerrain[1]);   //w
        terrainDecidingValues[2] += pow(30, countAdjacentTerrain[1]);   //h
        terrainDecidingValues[3] += pow(0, countAdjacentTerrain[1]);    //m
                                                                 //hills
        terrainDecidingValues[0] += pow(30, countAdjacentTerrain[2]);   //p
        terrainDecidingValues[1] += pow(25, countAdjacentTerrain[2]);   //w
        terrainDecidingValues[2] += pow(35, countAdjacentTerrain[2]);   //h
        terrainDecidingValues[3] += pow(20, countAdjacentTerrain[2]);   //m
                                                                 //mountain
        terrainDecidingValues[0] += pow(0, countAdjacentTerrain[3]);     //p
        terrainDecidingValues[1] += pow(0, countAdjacentTerrain[3]);     //w
        terrainDecidingValues[2] += pow(75, countAdjacentTerrain[3]);    //h
        terrainDecidingValues[3] += pow(25, countAdjacentTerrain[3]);    //m

        if(countAdjacentTerrain[0] != 0 || countAdjacentTerrain[1] != 0){
            terrainDecidingValues[3] *= 0.25;
        }

        if(countAdjacentTerrain[3] != 0){
            terrainDecidingValues[0] = 0.2;
            terrainDecidingValues[1] = 0.2;
        }

        int decValSum = 0;
        for(int i = 0; i < 4; i++)
            decValSum += terrainDecidingValues[i]; //determines total weight

        dice = rand()%decValSum+1;
        for(int i = 0; i < 4; i++)  {              //checks in which bracket the dice fell in
            if(dice <= terrainDecidingValues[i]) {
                switch(i) {
                    case 0: returnTerrain = 'p'; break;
                    case 1: returnTerrain = 'w'; break;
                    case 2: returnTerrain = 'h'; break;
                    case 3: returnTerrain = 'm'; break;
                }
                break;
            }
            else {
                dice -= terrainDecidingValues[i];
            }
        }
    }
    return returnTerrain;
}

bool Game::checkMapValidity(int numOfPlayers) {
    bool valid = false;
    int numOfCheck = (gridX-MAPCHECKOFFSET*2)*(gridY-MAPCHECKOFFSET*2);
    Resource* resource;
    MapCheck checkGrid[gridX-MAPCHECKOFFSET*2][gridY-MAPCHECKOFFSET*2]; //-MAPCHECKOFFSET*2 otherwise there's gonna be a crash

    for(int i = MAPCHECKOFFSET; i < gridX - MAPCHECKOFFSET; i++){
        for(int j = MAPCHECKOFFSET; j < gridY -MAPCHECKOFFSET; j++) {//stops at a square on map, records the resources around it
            checkGrid[i-MAPCHECKOFFSET][j-MAPCHECKOFFSET].x = i;
            checkGrid[i-MAPCHECKOFFSET][j-MAPCHECKOFFSET].y = j;
            for(int k = 0; k < 5; k++) {
                for(int l = 0; l < 5; l++) {
                    if(k == 3 && l == 3); //skips the central square - it gets destroyed if base is placed
                    else {
                        resource = grid[(i-MAPCHECKOFFSET)+k][(j-MAPCHECKOFFSET)+l]->getResource();

                        switch(resource->getType()){
                        case 'f': checkGrid[i-MAPCHECKOFFSET][j-MAPCHECKOFFSET].amountFood += resource->getAmount(); break;
                        case 'w': checkGrid[i-MAPCHECKOFFSET][j-MAPCHECKOFFSET].amountWood += resource->getAmount(); break;
                        case 'i': checkGrid[i-MAPCHECKOFFSET][j-MAPCHECKOFFSET].amountIron += resource->getAmount(); break;
                        case 'g': checkGrid[i-MAPCHECKOFFSET][j-MAPCHECKOFFSET].amountGold += resource->getAmount(); break;
                        }
                    }
                }
            }
        }
    }

    MapCheck avgCheck;

    for(int i = 0; i < gridX - MAPCHECKOFFSET*2; i++)
        for(int j = 0; j < gridY - MAPCHECKOFFSET*2; j++) {
            avgCheck.amountFood += checkGrid[i][j].amountFood;
            avgCheck.amountWood += checkGrid[i][j].amountWood;
            avgCheck.amountIron += checkGrid[i][j].amountIron;
            avgCheck.amountGold += checkGrid[i][j].amountGold;
        }
    avgCheck.amountFood /= numOfCheck;
    avgCheck.amountWood /= numOfCheck;
    avgCheck.amountIron /= numOfCheck;
    avgCheck.amountGold /= numOfCheck;

    avgCheck.amountFood = roundf(avgCheck.amountFood);
    avgCheck.amountWood = roundf(avgCheck.amountWood);
    avgCheck.amountIron = roundf(avgCheck.amountIron);
    avgCheck.amountGold = roundf(avgCheck.amountGold);

    qDebug() << "Avg resources:";
    qDebug() << "Food: " << avgCheck.amountFood;
    qDebug() << "Wood: " << avgCheck.amountWood;
    qDebug() << "Iron: " << avgCheck.amountIron;
    qDebug() << "Gold: " << avgCheck.amountGold;

    QList<MapCheck> validSquares; //a list of squares to choose from

    for(int i = 0; i < gridX - MAPCHECKOFFSET*2 ; i++)
        for(int j = 0; j < gridY - MAPCHECKOFFSET*2; j++) {
            if(checkGrid[i][j].amountFood >= avgCheck.amountFood - 2 && checkGrid[i][j].amountFood <= avgCheck.amountFood + 3) {
                if(checkGrid[i][j].amountWood >= avgCheck.amountWood - 1 && checkGrid[i][j].amountWood <= avgCheck.amountWood + 3) {
                    if(checkGrid[i][j].amountIron >= avgCheck.amountIron - 1 && checkGrid[i][j].amountIron <= avgCheck.amountIron + 3) {
                        if(checkGrid[i][j].amountGold >= avgCheck.amountGold && checkGrid[i][j].amountGold <= avgCheck.amountGold + 2) {
                            validSquares.push_back(checkGrid[i][j]);
                        }
                    }
                }
            }
        }

    qDebug() << "Prostih mest: " << validSquares.size() << "\n";
    QList<MapCheck> chosenSquares;
    int j = 0;
    float distance;
    bool farEnough;

    if(validSquares.size()!=0) {
        for(int i = 0; i < numOfPlayers; i++) { //select n squares sufficiently far apart
            if(i == 0) {         //for first square select first - nothing to compare to
                chosenSquares.push_back(validSquares.at(0));
            }
            else
            for(; j < validSquares.size(); j++) {
                farEnough = true;
                for(int k = 0; k < chosenSquares.size(); k++) {
                    distance = sqrt(pow(chosenSquares.at(k).x - validSquares.at(j).x, 2)
                                     + pow(chosenSquares.at(k).y - validSquares.at(j).y, 2));
                    if(distance < gridX/(numOfPlayers) + 1)
                        farEnough = false;
                }
                if(farEnough) { //went through loop without getting invalidated
                   chosenSquares.push_back(validSquares.at(j));
                }
            }
        }

        int pikeX = 0;
        int pikeY = 0;

        if(chosenSquares.size() == numOfPlayers) {
            for(int i = 0; i < chosenSquares.size(); i++) {
                new Base(players.at(i), grid[chosenSquares.at(i).x][chosenSquares.at(i).y]);
                new Worker(players.at(i), grid[chosenSquares.at(i).x][chosenSquares.at(i).y]);

                if(chosenSquares.at(i).x < gridX/2)
                    pikeX = 1;
                else if(chosenSquares.at(i).x > gridX/2)
                    pikeX = -1;

                if(chosenSquares.at(i).y < gridY/2)
                    pikeY = 1;
                else if(chosenSquares.at(i).y > gridY/2)
                    pikeY = -1;

                new Pikeman(players.at(i), grid[chosenSquares.at(i).x + pikeX][chosenSquares.at(i).y + pikeY]);
            }
            valid = true;
        }
    }
    return valid;
}

void Game::nextPlayer() {
    this->clearButtons();

    players.push_back(players.takeFirst());
    qDebug() << players.first()->getName();
    this->countdown(players.first());
    players.first()->startTurn();
}

void Game::countdown(Player* player) {
    player->updateStockpile();
    player->resetUnitMoves();

    if(player->isHuman())
        this->updateTopBar();

    for(QueueItem* queueItem: queue) {
        if(queueItem->getOwner() == player) {
            queueItem->countdown();
        }

    }
    if(selectedUnit) {
        selectedUnit = nullptr;
    }
    else if(selectedBuilding) {
        selectedBuilding = nullptr;
    }
}

void Game::checkForWinner() {
    if(players.size() == 1) {
        gameOver = true;
        w->victory->init(players.first());
        w->setScene(w->victory);
    }
}

void Game::setFoW(int i, int j, bool set) {
    if(i < gridX && i >= 0 && j < gridY && j >= 0)
        grid[i][j]->setFoW(set);
}

void Game::addQueueItem(QueueItem* item) {
    queue.push_back(item);
}

void Game::removeQueueItem(QueueItem* item) {
    int i = queue.indexOf(item);
    if(i != -1)
        queue.removeAt(i);
}

void Game::removePlayer(Player* player) {
    int i = players.indexOf(player);
    if(i != -1)
        players.removeAt(i);
}

void Game::workerButtons(Unit* actor) {
    bottomBar->workerButtons(actor);
}

void Game::soldierButtons(Unit* actor) {
    bottomBar->soldierButtons(actor);
}

void Game::fortButtons(Building* actor) {
    bottomBar->fortButtons(actor);
}

void Game::baseButtons(Building* actor) {
    bottomBar->baseButtons(actor);
}

void Game::buildingButtons(Building* actor) {
    bottomBar->buildingButtons(actor);
}

void Game::enemyUnitButtons(Unit* actor) {
    bottomBar->enemyUnitButtons(actor);
}

void Game::enemyBuildingButtons(Building* actor) {
    bottomBar->enemyBuildingButtons(actor);
}

void Game::clearButtons() {
    bottomBar->clearCurrentUnit();
    bottomBar->clearButtons();
}

void Game::wheelEvent(QGraphicsSceneWheelEvent *event) {
    event->accept();
}
