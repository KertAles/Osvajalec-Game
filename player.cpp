#include "mainwindow.h"
#include "player.h"
#include "ai.h"
#include "maprevealer.h"

extern MainWindow* w;

Player::Player(QString playerName, QColor col) {
   name = playerName;
   colour = col;

   human = false;
   ai = nullptr;

   stock.setFood(6);
   stock.setWood(4);
   stock.setIron(4);
   stock.setGold(0);

   foodIncome = 0;
   woodIncome = 0;
   ironIncome = 0;
   goldIncome = 0;
}

Player::~Player() {
    for( int i = 0; i < ownedBuildings.count(); i++) {
        if(ownedBuildings.at(i))
            delete ownedBuildings.at(i);
    }

    for( int i = 0; i < ownedUnits.count(); i++) {
        if(ownedUnits.at(i))
            delete ownedUnits.at(i);
    }
    if(ai)
        delete ai;
}

void Player::initAI() {
    ai = new AI(this);
}

QList<Building*> Player::getOwnedBuildings()
{ return ownedBuildings; }

QList<Unit*> Player::getOwnedUnits()
{ return ownedUnits; }

int Player::getFoodInc()
{ return foodIncome; }

int Player::getWoodInc()
{ return woodIncome; }

int Player::getIronInc()
{ return ironIncome; }

int Player::getGoldInc()
{ return goldIncome; }

Stockpile Player::getStockpile()
{ return stock; }

void Player::addUnit(Unit* newUnit) {
    ownedUnits.push_back(newUnit);
}

void Player::addBuilding(Building* newBuilding) {
    ownedBuildings.push_back(newBuilding);
}

void Player::removeUnit(Unit* delUnit) {
    int i = ownedUnits.indexOf(delUnit);
    if(i != -1)
        ownedUnits.removeAt(i);
}

void Player::removeBuilding(Building* delBuilding) {
    int i = ownedBuildings.indexOf(delBuilding);
    if(i != -1)
        ownedBuildings.removeAt(i);
}

void Player::clearNullPointers() {
    for( int i = 0; i < ownedBuildings.count(); i++) {
        if(!ownedBuildings.at(i))
            ownedBuildings.removeAt(i);
    }

    for( int i = 0; i < ownedUnits.count(); i++) {
        if(!ownedUnits.at(i))
            ownedUnits.removeAt(i);
    }
}

void Player::startTurn() {
    w->bah->activePlayer = this;
    if(human) {
        //mogoče bo še kaj tukaj
    }
    else {
        if(!w->bah->gameOver) {
            MapRevealer::revealMapAI(this);
            ai->resourceSearch();
            ai->unitRecruiter();

            ai->considerInvasion();
            if(ai->getInvasion()) {
                ai->checkForEnemies();
                ai->doInvasion();
            }
            else
                ai->armyMovement();

            QTime dieTime = QTime::currentTime().addMSecs(333); //waits a while
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            w->bah->nextPlayer();
        }
    }
}

void Player::destroyPlayer(Player* destroyer) {
    for(Building* building : ownedBuildings) {
        if(building->getType() != 'b') {
            if(building->getQueueItem()) {
                 building->deleteQueueItem();
            }
            building->setOwner(destroyer);
            destroyer->addBuilding(building);
            this->removeBuilding(building);
        }
    }

    for(Unit* unit : ownedUnits) {
        delete unit;
    }

    if(w->bah->localPlayer == this) {
        w->bah->localPlayer = nullptr;
        MapRevealer::uncoverMap();
    }

    InfluenceCalculator::removePlayer(this);
    w->bah->removePlayer(this);
    w->bah->checkForWinner();
}

void Player::updateIncome() {
    foodIncome = 0;
    woodIncome = 0;
    ironIncome = 0;
    goldIncome = 0;

    int amount;

    for(Unit* unit: ownedUnits) {
        amount = unit->getUpkeep().getAmount();
        switch(unit->getUpkeep().getResource()) {
            case 'f': foodIncome -= amount; break; //f is never the case, but you know
            case 'w': woodIncome -= amount; break;
            case 'i': ironIncome -= amount; break;
            case 'g': goldIncome -= amount; break;
        }
        foodIncome -= 2;
    }

    for(Building* building: ownedBuildings) {
        if(building->getPosition()->getResource()->isExploited()
                && building->getPosition()->getOwner() == this) {
            amount = building->getPosition()->getResource()->getAmount();
            switch(building->getPosition()->getResource()->getType()) {
                case 'f': foodIncome += amount; break;
                case 'w': woodIncome += amount; break;
                case 'i': ironIncome += amount; break;
                case 'g': goldIncome += amount; break;
            }
        }
        if(building->getType() == 'r') {
            goldIncome--;
        }
    }
    foodIncome += 3;
    woodIncome += 1;
    goldIncome += 1;

    w->bah->updateTopBar();
}

void Player::updateStockpile() {
    stock.setFood(foodIncome);
    stock.setWood(woodIncome);
    stock.setIron(ironIncome);
    stock.setGold(goldIncome);
}

void Player::resetUnitMoves() {
    for(Unit* unit : ownedUnits) {
        unit->resetMoves();
    }
}
