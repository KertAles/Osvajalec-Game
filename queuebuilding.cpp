#include "mainwindow.h"
#include "queuebuilding.h"

#include "Buildings\fort.h"
#include "Buildings\farm.h"
#include "Buildings\mine.h"
#include "Buildings\woodcamp.h"

extern MainWindow* w;

QueueBuilding::QueueBuilding(char role, Worker* unit) {
    owner = unit->getOwner();
    pos = unit->getPosition();
    creator = unit;
    type = role;

    unit->setQueueItem(this);
    w->bah->queue.push_back(this);

    switch(type) {
    case 'r': turnsLeft = 3; unit->getOwner()->takeGold(-3);
                             unit->getOwner()->takeIron(-3);
                             unit->getOwner()->takeWood(-5); break;

    case 'f': turnsLeft = 2; unit->getOwner()->takeWood(-1); break;
    case 'm': turnsLeft = 2; unit->getOwner()->takeWood(-1); break;
    case 'w': turnsLeft = 2; break;
    }
}

QueueBuilding::~QueueBuilding() {
    creator->unsetQueueItem();
    w->bah->removeQueueItem(this);
}

void QueueBuilding::createItem() {
    switch(type) {
    case 'r': new Fort(owner, pos); break;
    case 'f': new Farm(owner, pos); break;
    case 'm': new Mine(owner, pos); break;
    case 'w': new Woodcamp(owner, pos); break;
    }
    delete this;
}
