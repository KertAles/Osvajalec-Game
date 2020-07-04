#ifndef QUEUEUNIT_H
#define QUEUEUNIT_H

#include "queueitem.h"

class Building;

class QueueUnit : public QueueItem
{
    Building* creator;
public:
    QueueUnit(char role, Building* building);
    ~QueueUnit();

    void createItem();
};

#endif // QUEUEUNIT_H
