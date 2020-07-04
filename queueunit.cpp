#include "mainwindow.h"
#include "queueunit.h"

#include "Units\archer.h"
#include "Units\knight.h"
#include "Units\pikeman.h"
#include "Units\worker.h"

extern MainWindow* w;

QueueUnit::QueueUnit(char role, Building* building) {
    owner = building->getOwner();
    pos = building->getPosition();
    creator = building;
    type = role;

    w->bah->queue.push_back(this);
    building->setQueueItem(this);

    switch(type) {
    case 'a': turnsLeft = 2; building->getOwner()->takeFood(-1);
                             building->getOwner()->takeWood(-2); break;

    case 'k': turnsLeft = 2; building->getOwner()->takeFood(-1);
                             building->getOwner()->takeIron(-2); break;

    case 'p': turnsLeft = 2; building->getOwner()->takeFood(-1);
                             building->getOwner()->takeWood(-2); break;

    case 'w': turnsLeft = 2; building->getOwner()->takeFood(-1); break;
    }
}

QueueUnit::~QueueUnit() {
    creator->unsetQueueItem();
    w->bah->removeQueueItem(this);
}

void QueueUnit::createItem() {
    switch(type) {
    case 'a': new Archer(owner, pos); break;
    case 'k': new Knight(owner, pos); break;
    case 'p': new Pikeman(owner, pos); break;
    case 'w': new Worker(owner, pos); break;
    }
    delete this;
}
