#include "mainwindow.h"
#include "knight.h"

extern MainWindow* w;

Knight::Knight(Player* ownedBy, GridSquare* createPos) {
    owner = ownedBy;
    position = createPos;
    type = 'k';

    maxHp = 200;
    hp = maxHp;
    attack = 125;
    defense = 65;
    range = 1;
    los = 3;

    upkeep.setResource('w');
    upkeep.setAmount(1);

    maxMoves = 5;
    movesLeft = maxMoves;

    this->setPos(position->getX()+SQUARESIZE -(UNITSIZE + 7), position->getY() + 6);
    this->init();
    unitPix -> setPixmap(QPixmap(":/images/Units/knight.png"));
    w->bah->addItem(this);

    position->setUnit(this);
    owner -> addUnit(this);
    owner -> updateIncome();
    qDebug() << "Knight created";
}

Knight::~Knight() {
    if(w->bah->selectedUnit == this) {
        w->bah->selectedUnit = nullptr;
        w->bah->clearButtons();
    }
    position->unit = nullptr;
    owner -> removeUnit(this);

    if(!w->bah->destroying)
        owner->updateIncome();

    delete unitPix;
    delete background;
}

void Knight::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Knight leftclicked";
        w->bah->selectedBuilding = nullptr;
        w->bah->selectedUnit = this;
        w->bah->unitOrderType = 'm';

        if(this->getOwner() == w->bah->localPlayer)
            w->bah->soldierButtons(this);
        else
            w->bah->enemyUnitButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Knight rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Knight attacked";
            w->bah->selectedUnit->attackUnit(this);
        }
    }
}
