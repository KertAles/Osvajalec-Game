#include "mainwindow.h"
#include "gridsquare.h"
#include "influence.h"

extern MainWindow* w;

GridSquare::GridSquare() {
}

GridSquare::GridSquare(int i, int j) {
    x = i * SQUARESIZE;    //position on grid - in pixels
    y = j * SQUARESIZE + 50; //+50 because of top bar

    QList<Player*> players = w->bah->getPlayers();
    for(Player* player : players) {
        influence.push_back(new Influence(player));
    }

    resource = new Resource;
    owner = nullptr;
    unit = nullptr;
    building = nullptr;
    fow = true;
}

GridSquare::~GridSquare() {
    if(resource)
        delete resource;

    for(Influence* inf : influence) {
        delete inf;
    }
}

void GridSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter,option,widget);
    if(fow) {
        painter->setBrush(QBrush(QColor(50,50,50,165)));
        painter->drawRect(0.0f, 0.0f, SQUARESIZE, SQUARESIZE);
    }
    else {
        if(w->bah->selectedUnit && w->bah->unitOrderType == 'a') {
            if(w->bah->selectedUnit->getOwner() == w->bah->localPlayer
                    && w->bah->selectedUnit->getPosition() != this
                    && w->bah->selectedUnit->getMovesLeft()>=1) {
                if(w->bah->selectedUnit->inRange(this)) {
                    QPainterPath path;
                    path.addRect(QRect(2.0f, 2.0f, SQUARESIZE-6, SQUARESIZE-6));
                    painter->setPen(QPen(QColor(255,0,0), 6.0f));
                    painter->drawPath(path);
                }
            }
        }
        if(owner) {
            QPainterPath path;
            path.addRect(QRect(1.0f, 1.0f, SQUARESIZE-2, SQUARESIZE-2));
            painter->setPen(QPen(QColor(owner->getColour()), 4.0f));
            painter->drawPath(path);
        }
    }
}

int GridSquare::getX()
{ return x; }

int GridSquare::getY()
{ return y; }

char GridSquare::getTerrain()
{ return terrain; }

void GridSquare::setTerrain(char newTerrain){
    this -> terrain = newTerrain;
    this -> updateTerrainPicture();
}

float GridSquare::getCostToMove()
{ return costToMove; }

Unit* GridSquare::getUnit()
{ return unit; }

void GridSquare::setUnit(Unit* newUnit)
{ unit = newUnit; }

void GridSquare::unsetUnit()
{ unit = nullptr; }

Building* GridSquare::getBuilding()
{ return building; }

void GridSquare::setBuilding(Building* newBuilding)
{ building = newBuilding; }

void GridSquare::unsetBuilding()
{ building = nullptr; }

Resource* GridSquare::getResource()
{ return resource; }

void GridSquare::setFoW(bool set) {
     fow = set;
     if(fow) {
         if(unit)
            unit->setVisible(false);
         if(building)
            building->setVisible(false);
     }
     else {
         if(unit)
            unit->setVisible(true);
         if(building)
            building->setVisible(true);
         resource->reveal();
     }
}

void GridSquare::resetInfluence() {
    for(Influence* inf : influence) {
        inf->setValue(0);
    }
}

void GridSquare::setInfluence(Player* player, double val) {
    for(Influence* inf : influence) {
        if(player == inf->getPlayer()) {
            inf->setValue(inf->getValue()+val); //in case AoI overlaps
        }
    }
}

void GridSquare::removePlayer(Player* player) {
    for(Influence* inf : influence) {
        if(player == inf->getPlayer()) {
            influence.removeAt(influence.indexOf(inf));
        }
    }
}

Player* GridSquare::mostInfluentialPlayer() {
    Player* herr = nullptr;
    double maxVal = 0;

    for(Influence* inf : influence) {
        if(inf->getValue() > 0) {
            if(inf->getValue() > maxVal) {
                maxVal = inf->getValue();
                herr = inf->getPlayer();
            }
        }
    }
    return herr;
}

void GridSquare::updateTerrainPicture() {
    QString destination;

    switch(terrain)
    {
        case 'p': destination = ":/images/terrain/plain.png"; costToMove=1.0f; break;
        case 'w': destination = ":/images/terrain/wood.png"; costToMove=1.5f; break;
        case 'h': destination = ":/images/terrain/hill.png"; costToMove=2.0f; break;
        case 'm': destination = ":/images/terrain/mountain.png"; costToMove=3.0f; break;
    }

    terrainPixmap = QPixmap(destination);
    this -> setPixmap(terrainPixmap);
}

void GridSquare::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::RightButton) {
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'm') {
            if(!w->bah->selectedUnit->isMoving()) {
            qDebug() << "Grid " << x/SQUARESIZE << ", " << y/SQUARESIZE - 1;
            w->bah->selectedUnit->moveTo(this);
            }
            else
                qDebug() << "Če klikaš ne bo nič hitreje.";
        }
    }
}
