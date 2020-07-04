#ifndef WORKER_H
#define WORKER_H

#include "unit.h"

class Worker : public Unit
{
    QueueBuilding* queueItem;
public:
    Worker(Player* ownedBy, GridSquare* createPos);
    ~Worker();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QueueBuilding* getQueueItem();
    void setQueueItem(QueueBuilding* newItem);
    void deleteQueueItem();
    void undoQueueItem();
    void unsetQueueItem();
signals:

public slots:
};

#endif // WORKER_H
