#ifndef INFLUENCECALCULATOR_H
#define INFLUENCECALCULATOR_H

#include "gridsquare.h"

class Player;
class Building;

class InfluenceCalculator
{
public:
    InfluenceCalculator();
    static void calculateInfluence();
    static void calcSquareInfluence(GridSquare* square, Building* building);
    static void updateOwners();
    static void removePlayer(Player* player);
signals:

public slots:
};

#endif // INFLUENCECALCULATOR_H
