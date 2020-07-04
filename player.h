#ifndef PLAYER_H
#define PLAYER_H

#include "gridsquare.h"
#include "unit.h"
#include "building.h"
#include "stockpile.h"

#include <QString>
#include <QList>

class Unit;
class Building;
class AI;

class Player
{
    Stockpile stock;
    QColor colour;

    bool human;
    AI* ai;

    int foodIncome;
    int woodIncome;
    int ironIncome;
    int goldIncome;

    QList<Unit*> ownedUnits;
    QList<Building*> ownedBuildings;
public:
    QString name;

    Player(QString playerName, QColor colour);
    ~Player();

    void startTurn();
    void destroyPlayer(Player* destroyer);

    void initAI();
    AI* getAI() { return ai; }
    bool isHuman() { return human; }
    void setHuman(bool hmn) { human = hmn; }
    QList<Unit*> getOwnedUnits();
    QList<Building*> getOwnedBuildings();
    int getFoodInc();
    int getWoodInc();
    int getIronInc();
    int getGoldInc();
    Stockpile getStockpile();
    QColor getColour() { return colour; }
    QString getName() { return name; }
    void setColour(QColor nju) { colour = nju; }
    void takeFood(int amount) { stock.setFood(amount); }
    void takeWood(int amount) { stock.setWood(amount); }
    void takeIron(int amount) { stock.setIron(amount); }
    void takeGold(int amount) { stock.setGold(amount); }

    void updateIncome();
    void addUnit(Unit* newUnit);
    void addBuilding(Building* newBuilding);
    void removeUnit(Unit* delUnit);
    void removeBuilding(Building* delBuilding);
    void clearNullPointers();
    void updateStockpile();
    void resetUnitMoves();
};

#endif // PLAYER_H
