#ifndef QUEUEBUILDING_H
#define QUEUEBUILDING_H

#include "gridsquare.h"
#include "player.h"
#include "Units/worker.h"
#include "queueitem.h"

class QueueBuilding : public QueueItem
{
    Worker* creator;
public:
    QueueBuilding(char role, Worker* unit);
    ~QueueBuilding();

    void createItem();
};

#endif // QUEUEBUILDING_H
