#ifndef AI_H
#define AI_H

#include "aivision.h"
#include "resourcedemand.h"

#include <QVector>

class Player;

class AI
{
    Player* player;
    ResourceDemand resDemand;
    QVector<QVector<AIVision*>> vision;

    bool invasion;
public:
    AI(Player* plyr);
    ~AI();

    AIVision* getAIVision(int i, int j) { return vision[i][j]; }

    bool getInvasion() { return invasion; }

    void resourceSearch();
    void updateResDemand();
    GridSquare* resDecision(Unit* worker, char res);
    void makeResBuilding(Unit* worker);
    void queueResBuilding(Unit* worker, char res);

    void unitRecruiter();
    int countUnusedRes();
    void buildArmy();

    void fortPlacement(char res);
    GridSquare* searchForFortSpot(GridSquare* resPos);

    void armyMovement();
    bool checkForEnemies();
    Unit* bestUnitForAttack(Unit* enemy);
    Unit* bestUnitForAttack(Building* enemy);
    void moveUnits();
    GridSquare* findUnitsChillSquare(Unit* unit);

    void considerInvasion();
    void doInvasion();
    void moveUnitsTowards(Building* base);
};

#endif // AI_H
