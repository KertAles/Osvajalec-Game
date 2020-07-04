#include "mainwindow.h"
#include "gridsquare.h"
#include "resource.h"

#include <QtDebug>

extern MainWindow* w;

Resource::Resource() {
    resourceEllipse = new QGraphicsEllipseItem;
    amountText = new QGraphicsPixmapItem;
    resourceEllipse->setZValue(0.8f);
    amountText->setZValue(0.9f);

    this->addToGroup(resourceEllipse);
    this->addToGroup(amountText);

    defPen = resourceEllipse->pen();

    exploited = false;
}

Resource::~Resource() {
    if(resourceEllipse)
        delete resourceEllipse;

    if(amountText)
        delete amountText;
}

char Resource::getType()
{ return type; }

int Resource::getAmount()
{ return amount; }

void Resource::exploit(bool status)
{ exploited = status; }

bool Resource::isExploited()
{ return exploited; }

void Resource::generateResource(GridSquare *currentSquare) {
    int dice = rand()%100;

    if(currentSquare -> getTerrain() == 'p') //plains
        this -> rollPlains(dice);
    else if(currentSquare -> getTerrain() == 'w') // woods
        this -> rollWoods(dice);
    else if(currentSquare -> getTerrain() == 'h') //hills
        this -> rollHills(dice);
    else if(currentSquare -> getTerrain() == 'm') //mountains
        this -> rollMountains(dice);

    reloadResourcePixmaps();
    this -> setPos(currentSquare->getX(), currentSquare->getY());
}

void Resource::rollPlains(int dice) {
    if(dice < 90) { //food
        dice = rand()%100;
        if(dice < 68) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'f';
            if(dice < 80) {
                amount = 1;
            }
            else if(dice < 89) {
                amount = 2;
            }
            else if(dice < 95) {
                amount = 3;
            }
            else if(dice < 98) {
                amount = 4;
            }
            else amount = 5;
        }
    }
    else {          //else gold
        dice = rand()%100;
        if(dice < 85) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'g';
            if(dice < 95) {
                amount = 1;
            }
            else if(dice < 99) {
                amount = 2;
            }
            else amount = 3;
        }
    }
}

void Resource::rollWoods(int dice) {
    if(dice < 85) { //wood
        dice = rand()%100;
        if(dice < 60) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'w';
            if(dice < 70) {
                amount = 1;
            }
            else if(dice < 80) {
                amount = 2;
            }
            else if(dice < 93) {
                amount = 3;
            }
            else if(dice < 98) {
                amount = 4;
            }
            else amount = 5;
        }
    }
    else {          //else gold
        dice = rand()%100;
        if(dice < 85) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'g';
            if(dice < 90) {
                amount = 1;
            }
            else if(dice < 99) {
                amount = 2;
            }
            else amount = 3;
        }
    }
}

void Resource::rollHills(int dice) {
    if(dice < 70) { //iron
        dice = rand()%100;
        if(dice < 70) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'i';
            if(dice < 80) {
                amount = 1;
            }
            else if(dice < 89) {
                amount = 2;
            }
            else if(dice < 94) {
                amount = 3;
            }
            else if(dice < 98) {
                amount = 4;
            }
            else amount = 5;
        }
    }
    else {          //else gold
        dice = rand()%100;
        if(dice < 70) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'g';
            if(dice < 85) {
                amount = 1;
            }
            else if(dice < 95) {
                amount = 2;
            }
            else amount = 3;
        }
    }
}

void Resource::rollMountains(int dice) {
    if(dice < 60) { //iron
        dice = rand()%100;
        if(dice < 50) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'i';
            if(dice < 65) {
                amount = 1;
            }
            else if(dice < 75) {
                amount = 2;
            }
            else if(dice < 85) {
                amount = 3;
            }
            else if(dice < 95) {
                amount = 4;
            }
            else amount = 5;
        }
    }
    else {          //else gold
        dice = rand()%100;
        if(dice < 40) {
            amount = 0;
            type = 'n';
        }
        else {
            type = 'g';
            if(dice < 70) {
                amount = 1;
            }
            else if(dice < 90) {
                amount = 2;
            }
            else if(dice < 97)
                amount = 3;
            else amount = 4;
        }
    }
}

void Resource::addToScene() {
    w->bah->addItem(this);
    this->setPos(this->pos().x()+6.0f, this->pos().y()+6.0f);
}

void Resource::hideResource() {
    this->setVisible(false);
}

void Resource::disableResource() {
    disabled = true;
    this -> reloadResourcePixmaps();
}

void Resource::enableResource() {
    disabled = false;
    this -> reloadResourcePixmaps();
}

void Resource::reveal() {
    this->setVisible(true);
}

void Resource::reloadResourcePixmaps() {
    if(!disabled) {
        resourceEllipse->setRect(0.0f, 0.0f, RESOURCESIZE, RESOURCESIZE);

        switch(type) {
        case 'f': resourceEllipse->setBrush(QBrush(QColor(200, 230, 95))); break;
        case 'w': resourceEllipse->setBrush(QBrush(QColor(150, 111, 51))); break;
        case 'i': resourceEllipse->setBrush(QBrush(QColor(67, 75, 77))); break;
        case 'g': resourceEllipse->setBrush(QBrush(QColor(218,165,32))); break;
        case 'n': resourceEllipse->setBrush(Qt::NoBrush); break;
        }

        if(type == 'n') {
            resourceEllipse->setPen(Qt::NoPen);
        }
        else {
            resourceEllipse->setPen(defPen);
        }

        amountText -> setPixmap(":/images/resources/"+QString::number(amount)+".png");
    }
    else {
        resourceEllipse->setPen(Qt::NoPen);
        resourceEllipse->setBrush(Qt::NoBrush);
        amountText->setPixmap(":/images/resources/"+QString::number(0)+".png");
    }
}
