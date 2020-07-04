#include "mainwindow.h"
#include "unit.h"
#include "units\worker.h"
#include "queuebuilding.h"
#include "pathfinding\bresenham.h"
#include "maprevealer.h"
#include "unitmover.h"

#include <math.h>
#include <QDebug>

extern MainWindow* w;

Unit::Unit() {

}

void Unit::init() {
    unitPix = new QGraphicsPixmapItem;
    unitPix->setZValue(0.9f);
    unitPix->setPos(this->pos());

    background = new QGraphicsEllipseItem;
    background->setPen(Qt::NoPen);
    background->setRect(0.0f, 0.0f, UNITSIZE, UNITSIZE);
    background->setPos(this->pos());
    background->setBrush(Qt::white);
    background->setZValue(0.8f);

    this->addToGroup(background);
    this->addToGroup(unitPix);

    moving = false;
}

void Unit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsItemGroup::paint(painter,option,widget);
    if(owner) {
        QPainterPath circlePath;
        circlePath.addEllipse(QRect(0.0f, 1.0f, UNITSIZE, UNITSIZE));
        painter->setPen(QPen(QColor(owner->getColour()), 5.0f));
        painter->setBrush(QBrush(owner->getColour()));
        painter->drawPath(circlePath);
    }
    if(this != w->bah->selectedUnit) { //is done for the turn
        if(this->movesLeft == 0)
            background->setBrush(QBrush(QColor(255 , 170 , 170)));
        else
            background->setBrush(QBrush(QColor(255 , 255 , 255)));
        if(this->getType() == 'w') {
            Worker* tmp = (Worker*) this;
            if(tmp->getQueueItem())
                background->setBrush(QBrush(QColor(150 , 255 , 150)));
        }
    }
    else {
        background->setBrush(QBrush(QColor(250 , 239 , 122)));
    }
}

GridSquare* Unit::getPosition(){
    return position;
}

Player* Unit::getOwner(){
    return owner;
}

int Unit::getLoS()
{ return los; }

void Unit::move(GridSquare* newPos) {
    if(!this->position->getFow())
        UnitMover::moveSmooth(this, newPos);
    else
        this->setPos(position->getX()+SQUARESIZE -(UNITSIZE + 7), position->getY() + 6);

    this->position->unsetUnit();
    this->position = newPos;
    this->position->setUnit(this);

    if(this->type == 'w' && this->getOwner() == w->bah->localPlayer) { //when worker moves, queueItem gets deleted
        Worker* tmp = (Worker*)this;
        if(tmp->getQueueItem()) {

            switch(tmp->getQueueItem()->getType()) {
            case 'r': tmp->getOwner()->takeGold(2); tmp->getOwner()->takeIron(3); tmp->getOwner()->takeWood(6); break;
            case 'f': tmp->getOwner()->takeWood(1); break;
            case 'w': break;
            case 'm': tmp->getOwner()->takeWood(1); break;
            }

            w->bah->updateTopBar();
            w->bah->removeQueueItem((QueueItem*)tmp->getQueueItem());
            tmp->deleteQueueItem();
            qDebug() << "QueueItem removed";
        }
        w->bah->workerButtons(this);
    }

    movesLeft -= newPos->getCostToMove();

    if(this->getOwner() == w->bah->localPlayer) {
        MapRevealer::revealMap(w->bah->localPlayer);
    }
}

void Unit::moveTo(GridSquare* newPos) {
    QList<GridSquare*> path = Bresenham::findPath(this, newPos);
    moving = true;
    bool canMove = true;
    while(canMove) {
        if(path.size() != 0) {
            if(movesLeft < path.first()->getCostToMove())
                canMove = false;

            if(path.first()->getBuilding())
                if(path.first()->getBuilding()->doesBlock())
                    canMove = false;

            if(path.first()->getUnit())
                canMove = false;

            if(canMove) {
                move(path.first());
                path.removeFirst();
            }
        }
        else
            canMove = false;
    }
    moving = false;
}

bool Unit::inRange(Unit* enemy) {
    if(abs(position->getX()/SQUARESIZE - enemy->getPosition()->getX()/SQUARESIZE) > range
        || abs(position->getY()/SQUARESIZE - enemy->getPosition()->getY()/SQUARESIZE) > range)
        return false;
    else return true;
}

bool Unit::inRange(Building* enemy) {
    if(abs(position->getX()/SQUARESIZE - enemy->getPosition()->getX()/SQUARESIZE) > range
       || abs(position->getY()/SQUARESIZE - enemy->getPosition()->getY()/SQUARESIZE) > range)
        return false;
    else return true;
}

bool Unit::inRange(GridSquare* pos) {
    if(abs(position->getX()/SQUARESIZE - pos->getX()/SQUARESIZE) > range
       || abs(position->getY()/SQUARESIZE - pos->getY()/SQUARESIZE) > range)
        return false;
    else return true;
}

void Unit::attacked(int dmg, Unit* opponent) {
    int finalDmg = dmg;

    if(type == 'k') { //if knight
        if(opponent->getType() == 'p')
            finalDmg*=1.75;
        if(opponent->getType() == 'a')
            finalDmg*=0.75;
    }

    if(type == 'a') { //if archer
        if(opponent->getType() == 'k')
            finalDmg*=1.5;
        if(opponent->getType() == 'p')
            finalDmg*=0.75;
    }

    if(type == 'p') { //if pike
        if(opponent->getType() == 'a')
            finalDmg*=1.5;
        if(opponent->getType() == 'k')
            finalDmg*=0.75;
    }

    hp = hp - finalDmg;
}

int Unit::biteBack(Unit* opponent) {
    int finalDmg = defense;
    if(inRange(opponent)) {
        if(type == 'k') { //if knight
            if(opponent->getType() == 'a')
                finalDmg*=1.5;
            if(opponent->getType() == 'p')
                finalDmg*=0.75;
        }

        if(type == 'a') { //if archer
            if(opponent->getType() == 'p')
                finalDmg*=1.5;
            if(opponent->getType() == 'k')
                finalDmg*=0.75;
            UnitMover::biteBack(this, opponent);
        }

        if(type == 'p') { //if pike
            if(opponent->getType() == 'k')
                finalDmg*=1.75;
            if(opponent->getType() == 'a')
                finalDmg*=0.75;
        }
    }
    else
        finalDmg = 0;

    return finalDmg;
}

bool Unit::attackUnit(Unit *enemy) {
    bool destroyed = false;

    if(this->movesLeft >= 1) {
        if(this->inRange(enemy)) {
            if(owner != enemy->getOwner()) {
                enemy->attacked(attack, this);
                hp = hp - enemy->biteBack(this);

                UnitMover::attack(this, enemy);
                movesLeft-=2;
                if(movesLeft<0)
                    movesLeft = 0;

                if(enemy->getHp() <= 0) {
                    destroyed = true;
                    delete enemy;
                }

                if(hp <= 0) {
                    if(w->bah->activePlayer == w->bah->localPlayer) {
                        delete this;
                        w->bah->clearButtons();
                    }
                }
                /*else {
                    if(type == 'w')
                        w->bah->workerButtons(w->bah->selectedUnit);
                    else
                        w->bah->soldierButtons(w->bah->selectedUnit);
                }*/
            }
            else
                qDebug() << "Can't attack your own!";
        }
        else
            qDebug() << "Not in range!";
    }
    else
        qDebug() << "Not enough moves";

    return destroyed;
}

bool Unit::attackBuilding(Building *enemy) {
    bool destroyed = false;

    if(this->movesLeft >= 1) {
        if(this->inRange(enemy)) {
            if(owner != enemy->getOwner()) {
                enemy->attacked(attack);
                UnitMover::attack(this, enemy);

                hp = hp - enemy->biteBack();

                if(enemy->getDefense() != 0) {
                    UnitMover::biteBack(enemy, this);
                }

                movesLeft-=2;
                if(movesLeft<0)
                    movesLeft = 0;

                if(enemy->getHp() <= 0) {
                    if(enemy->getType() == 'b') {
                        if(w->bah->activePlayer == w->bah->localPlayer) {
                            enemy->getOwner()->destroyPlayer(owner); //transfers all buildings
                            delete enemy->getOwner();
                        }
                        destroyed = true;
                    }
                    else {
                        if(w->bah->activePlayer == w->bah->localPlayer)
                            delete enemy;
                        destroyed = true;
                    }
                }

                if(hp <= 0) {
                    if(w->bah->activePlayer == w->bah->localPlayer) {
                        delete this;
                        w->bah->clearButtons();
                    }
                }
                /*else {
                    if(type == 'w')
                        w->bah->workerButtons(w->bah->selectedUnit);
                    else
                        w->bah->soldierButtons(w->bah->selectedUnit);
                }*/
            }
            else
                qDebug() << "Can't attack your own!";
        }
        else
            qDebug() << "Not in range!";
    }
    else
        qDebug() << "Not enough moves";

    return destroyed;
}

void Unit::attackUnitAI(Unit* enemy) {
    QList<GridSquare*> path = Bresenham::findPath(this, enemy->getPosition());

    bool inRange = false;
    bool canMove = true;

    if(this->inRange(enemy))
        inRange = true;

    while(canMove && !inRange) {
        if(path.size() != 0) {
            if(movesLeft < path.first()->getCostToMove())
                canMove = false;

            if(path.first()->getBuilding())
                if(path.first()->getBuilding()->doesBlock())
                    canMove = false;

            if(path.first()->getUnit())
                canMove = false;

            if(canMove) {
                move(path.first());
                path.removeFirst();
                if(this->inRange(enemy))
                    inRange = true;
            }
        }
        else
            canMove = false;
    }

    bool enemyDied = false;

    while(movesLeft >= 1 && !enemyDied && inRange && hp > 0) {
        enemyDied = this->attackUnit(enemy);
    }
    if(hp <= 0)
        delete this;
}

void Unit::attackBuildingAI(Building* enemy) {
    QList<GridSquare*> path = Bresenham::findPath(this, enemy->getPosition());

    bool inRange = false;
    bool canMove = true;

    if(this->inRange(enemy))
        inRange = true;

    while(canMove && !inRange) {
        if(path.size() != 0) {
            if(movesLeft < path.first()->getCostToMove())
                canMove = false;

            if(path.first()->getBuilding())
                if(path.first()->getBuilding()->doesBlock())
                    canMove = false;

            if(path.first()->getUnit())
                canMove = false;

            if(canMove) {
                move(path.first());
                path.removeFirst();

                if(this->inRange(enemy))
                    inRange = true;
            }
        }
        else
            canMove = false;
    }

    bool enemyDied = false;

    while(movesLeft >= 1 && !enemyDied && inRange && hp > 0) {
        enemyDied = this->attackBuilding(enemy);
    }
    if(hp <= 0)
        delete this;

    if(enemyDied) {
        if(enemy->getType() == 'b') {
            enemy->getOwner()->destroyPlayer(owner); //transfers all buildings
            delete enemy->getOwner();
        }
        else {
            delete enemy;
        }
    }
}
