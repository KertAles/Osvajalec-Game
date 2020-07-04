#include "mainwindow.h"
#include "building.h"
#include "queueunit.h"

extern MainWindow* w;

Building::Building()
{

}

void Building::init() {
    buildPix = new QGraphicsPixmapItem;
    buildPix->setZValue(0.9f);
    buildPix->setPos(this->pos());

    background = new QGraphicsEllipseItem;
    background->setPen(Qt::NoPen);
    background->setRect(0.0f, 0.0f, UNITSIZE, UNITSIZE);
    background->setPos(this->pos());
    background->setBrush(Qt::white);
    background->setZValue(0.8f);

    this->addToGroup(background);
    this->addToGroup(buildPix);
}

void Building::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsItemGroup::paint(painter,option,widget);
    if(owner) {
        QPainterPath circlePath;
        circlePath.addEllipse(QRect(0.0f, 1.0f, BUILDINGSIZE, BUILDINGSIZE));
        painter->setPen(QPen(QColor(owner->getColour()), 5.0f));
        painter->setBrush(QBrush(owner->getColour()));
        painter->drawPath(circlePath);
    }
    if(this != w->bah->selectedBuilding) {
        if(this->queueItem)
            background->setBrush(QBrush(QColor(150 , 255 , 150)));
        else
            background->setBrush(QBrush(QColor(255 , 255 , 255)));
    }
    else {
        background->setBrush(QBrush(QColor(250 , 239 , 122)));
    }
}

bool Building::doesBlock() {
    return blocksMovement;
}

Player* Building::getOwner()
{ return owner; }

int Building::getLoS()
{ return los; }

GridSquare* Building::getPosition()
{ return position; }

void Building::attacked(int atk) {
    hp = hp - atk;
}

int Building::biteBack() {
    return defense;
}

void Building::setQueueItem(QueueUnit* newItem) {
    if(queueItem) {
        switch(queueItem->getType()) {
        case 'a': owner->takeFood(1); owner->takeWood(2); break;
        case 'p': owner->takeFood(1); owner->takeWood(2); break;
        case 'k': owner->takeFood(1); owner->takeIron(2);break;
        case 'w': owner->takeFood(1); break;
        }

        w->bah->updateTopBar();
        w->bah->removeQueueItem((QueueItem*)queueItem);
        delete queueItem;
        qDebug() << "QueueItem replaced";
    }
    queueItem = newItem;
}

void Building::unsetQueueItem() {
    queueItem = nullptr;
}

void Building::undoQueueItem() {
    if(queueItem) {
        switch(queueItem->getType()) {
        case 'a': owner->takeFood(1); owner->takeWood(2); break;
        case 'p': owner->takeFood(1); owner->takeWood(2); break;
        case 'k': owner->takeFood(1); owner->takeIron(2);break;
        case 'w': owner->takeFood(1); break;
        }

        w->bah->updateTopBar();
        w->bah->removeQueueItem((QueueItem*)queueItem);
        delete queueItem;
        qDebug() << "QueueItem deleted";
    }
    queueItem = nullptr;
}

void Building::deleteQueueItem()
{ delete queueItem; }

QueueUnit* Building::getQueueItem()
{ return queueItem; }
