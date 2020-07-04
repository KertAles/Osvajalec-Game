#ifndef INFLUENCE_H
#define INFLUENCE_H

#include "player.h"

class Influence
{
    double value;
    Player* player;
public:
    Influence(Player* plyr);
    double getValue() { return value; }
    Player* getPlayer() { return player; }
    void setValue(double val) { value = val; }
};

#endif // INFLUENCE_H
