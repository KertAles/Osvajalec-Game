#include "mainwindow.h"
#include "worker.h"
#include "queuebuilding.h"

#include <QDebug>

extern MainWindow* w;

Worker::Worker(Player* ownedBy, GridSquare* createPos) {
    owner = ownedBy;
    position = createPos;
    type = 'w';

    maxHp = 50;
    hp = maxHp;
    attack = 15;
    defense = 15;
    range = 1;
    los = 2;

    upkeep.setResource('f');
    upkeep.setAmount(-1);

    maxMoves = 3;
    movesLeft = maxMoves;

    queueItem = nullptr;

    this->setPos(position->getX()+SQUARESIZE -(UNITSIZE + 7), position->getY() + 6);
    this->init();
    unitPix -> setPixmap(QPixmap(":/images/Units/worker.png"));
    w->bah->addItem(this);

    position->setUnit(this);
    owner -> addUnit(this);
    owner -> updateIncome();
    qDebug() << "Worker created";
}

Worker::~Worker() {
    if(w->bah->selectedUnit == this) {
        w->bah->selectedUnit = nullptr;
        w->bah->clearButtons();
    }

    position->unit = nullptr;
    owner -> removeUnit(this);

    if(queueItem)
        delete queueItem;

    if(!w->bah->destroying)
        owner->updateIncome();


    delete unitPix;
    delete background;
}

void Worker::mousePressEvent(QGraphicsSceneMouseEvent *event) {    
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Worker leftclicked";
        w->bah->selectedBuilding = nullptr;
        w->bah->selectedUnit = this;
        w->bah->unitOrderType = 'm';

        if(this->getOwner() == w->bah->localPlayer) {
            w->bah->workerButtons(w->bah->selectedUnit);
        }
        else
            w->bah->enemyUnitButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Worker rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Worker attacked";
            w->bah->selectedUnit->attackUnit(this);
        }
    }
}

void Worker::setQueueItem(QueueBuilding* newItem) {
    if(queueItem) {
        switch(queueItem->getType()) {
        case 'r': owner->takeGold(2); owner->takeIron(3); owner->takeWood(6); break;
        case 'f': owner->takeWood(1); break;
        case 'w': break;
        case 'm': owner->takeWood(1); break;
        }

        w->bah->updateTopBar();
        w->bah->removeQueueItem((QueueItem*)queueItem);
        delete queueItem;
        qDebug() << "Queue item changed";
    }
    queueItem = newItem;
}

void Worker::unsetQueueItem() {
    queueItem = nullptr;
}

void Worker::undoQueueItem() {
    if(queueItem) {
        switch(queueItem->getType()) {
        case 'r': owner->takeGold(2); owner->takeIron(3); owner->takeWood(6); break;
        case 'f': owner->takeWood(1); break;
        case 'w': break;
        case 'm': owner->takeWood(1); break;
        }

        w->bah->updateTopBar();
        w->bah->removeQueueItem((QueueItem*)queueItem);
        delete queueItem;
        qDebug() << "Queue deleted";
    }
    queueItem = nullptr;
}

void Worker::deleteQueueItem() {
    if(queueItem)
        delete queueItem;
    queueItem = nullptr;
}

QueueBuilding* Worker::getQueueItem()
{ return queueItem; }
