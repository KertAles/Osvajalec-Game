#ifndef UNITMOVER_H
#define UNITMOVER_H

#include "unit.h"
#include "building.h"

class UnitMover
{
public:
    UnitMover();

    static void moveSmooth(Unit* unit, GridSquare* pos);
    static void attack(Unit* attacker, Unit* defender);
    static void attack(Unit* attacker, Building* defender);
    static void biteBack(Building *defender, Unit *attacker);
    static void biteBack(Unit *defender, Unit *attacker);

signals:

public slots:
};

#endif // UNITMOVER_H
