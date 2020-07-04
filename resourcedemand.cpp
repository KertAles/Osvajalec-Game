#include "resourcedemand.h"
#include "Units/worker.h"
#include "queuebuilding.h"

#include <cmath>

ResourceDemand::ResourceDemand() { }

ResourceDemand::ResourceDemand(Player* plyr) {
    player = plyr;
    foodDemand = 0;
    woodDemand = 0;
    ironDemand = 0;
    goldDemand = 0;
}

void ResourceDemand::updateFoodDemand() {
    int income = player->getFoodInc();
    foodDemand = 0;

    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType() == 'w') {
            Worker* worker = (Worker*) unit;
            if(worker->getQueueItem()) {
                if(worker->getQueueItem()->getType() == 'f') { //queued farm
                    income += worker->getPosition()->getResource()->getAmount();
                }
            }
        }
    }

    if(income < -5) {
        if(player->getStockpile().getFood() <= 0) {
            if (player->getStockpile().getFood() == 0)
                foodDemand += 20;
            else
                foodDemand += 20 * abs(player->getStockpile().getFood());
        }
        else
            foodDemand += 10 * (10.0 / player->getStockpile().getFood());
    }
    else if(income == 0) {
        if(player->getStockpile().getFood() < 4)
            foodDemand += 10;
        else
            foodDemand += 5;
    }
    else if(income < 4) {
        if(player->getStockpile().getFood() < -5)
            foodDemand += 5;
        else
            foodDemand += -3;
    }
    else
        foodDemand += -10 * player->getStockpile().getFood();
}

void ResourceDemand::updateWoodDemand() {
    int income = player->getWoodInc();
    woodDemand = 0;

    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType() == 'w') {
            Worker* worker = (Worker*) unit;
            if(worker->getQueueItem()) {
                if(worker->getQueueItem()->getType() == 'w') { //queued woodcamp
                    income += worker->getPosition()->getResource()->getAmount();
                }
            }
        }
    }

    if(income < -5) {
        if(player->getStockpile().getWood() <= 0) {
            if (player->getStockpile().getWood() == 0)
                woodDemand += 20;
            else
                woodDemand += 20 * abs(player->getStockpile().getWood());
        }
        else
            woodDemand += 10 * (10.0 / player->getStockpile().getWood());
    }
    else if(income == 0) {
        if(player->getStockpile().getWood() < 4)
            woodDemand += 10;
        else
            woodDemand += 5;
    }
    else if(income < 4) {
        if(player->getStockpile().getWood() < -5)
            woodDemand += 5;
        else
            woodDemand += -3;
    }
    else
        woodDemand += -10 * player->getStockpile().getWood();
}

void ResourceDemand::updateIronDemand() {
    int income = player->getIronInc();
    ironDemand = 0;

    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType() == 'w') {
            Worker* worker = (Worker*) unit;
            if(worker->getQueueItem()) {
                if(worker->getQueueItem()->getType() == 'm') { //queued mine
                    if(worker->getPosition()->getResource()->getType() == 'i') //mine for iron
                        income += worker->getPosition()->getResource()->getAmount();
                }
            }
        }
    }

    if(income < -5) {
        if(player->getStockpile().getIron() <= 0) {
            if (player->getStockpile().getIron() == 0)
                ironDemand += 20;
            else
                ironDemand += 20 * abs(player->getStockpile().getIron());
        }
        else
            ironDemand += 10 * (10.0 / player->getStockpile().getIron());
    }
    else if(income == 0) {
        if(player->getStockpile().getIron() < 4)
            ironDemand += 10;
        else
            ironDemand += 5;
    }
    else if(income < 3) {
        if(player->getStockpile().getIron() < -5)
            ironDemand += 5;
        else
            ironDemand += -3;
    }
    else
        ironDemand += -10 * player->getStockpile().getIron();
}

void ResourceDemand::updateGoldDemand() {
    int income = player->getGoldInc();
    goldDemand = 0;

    for(Unit* unit : player->getOwnedUnits()) {
        if(unit->getType() == 'w') {
            Worker* worker = (Worker*) unit;
            if(worker->getQueueItem()) {
                if(worker->getQueueItem()->getType() == 'm') { //queued mine
                    if(worker->getPosition()->getResource()->getType() == 'g') //mine for gold
                    income += worker->getPosition()->getResource()->getAmount();
                }
            }
        }
    }

    if(income < -1) {
        if(player->getStockpile().getGold() <= 0) {
            if (player->getStockpile().getGold() == 0)
                goldDemand += 20;
            else
                goldDemand += 20 * abs(player->getStockpile().getGold());
        }
        else
            goldDemand += 10 * (10.0 / player->getStockpile().getGold());
    }
    else if(income == 0) {
        if(player->getStockpile().getGold() < 2)
            goldDemand += 10;
        else
            goldDemand += 5;
    }
    else if(income < 3) {
        if(player->getStockpile().getGold() < -4)
            goldDemand += 5;
        else
            goldDemand += -3;
    }
    else
        goldDemand += -10 * player->getStockpile().getGold();
}
