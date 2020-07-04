#ifndef RESOURCEDEMAND_H
#define RESOURCEDEMAND_H

#include "player.h"

class ResourceDemand
{
    Player* player;
    double foodDemand;
    double woodDemand;
    double ironDemand;
    double goldDemand;
public:
    ResourceDemand();
    ResourceDemand(Player* plyr);

    double getFoodDemand() { return foodDemand; }
    double getWoodDemand() { return woodDemand; }
    double getIronDemand() { return ironDemand; }
    double getGoldDemand() { return goldDemand; }

    void updateFoodDemand();
    void updateWoodDemand();
    void updateIronDemand();
    void updateGoldDemand();

};

#endif // RESOURCEDEMAND_H
