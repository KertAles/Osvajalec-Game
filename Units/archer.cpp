#include "mainwindow.h"
#include "archer.h"

extern MainWindow* w;

Archer::Archer(Player* ownedBy, GridSquare* createPos) {
    owner = ownedBy;
    position = createPos;
    type = 'a';

    maxHp = 125;
    hp = maxHp;
    attack = 100;
    defense = 30;
    range = 2;
    los = 4;

    upkeep.setResource('w');
    upkeep.setAmount(1);

    maxMoves = 3;
    movesLeft = maxMoves;

    this->setPos(position->getX()+SQUARESIZE -(UNITSIZE + 7), position->getY() + 6);
    this->init();
    unitPix -> setPixmap(QPixmap(":/images/Units/archer.png"));
    w->bah->addItem(this);


    position->setUnit(this);
    owner -> addUnit(this);
    owner -> updateIncome();
    qDebug() << "Archer created";
}

Archer::~Archer() {
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

void Archer::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Archer leftclicked";
        w->bah->selectedBuilding = nullptr;
        w->bah->selectedUnit = this;
        w->bah->unitOrderType = 'm';

        if(this->getOwner() == w->bah->localPlayer)
            w->bah->soldierButtons(this);
        else
            w->bah->enemyUnitButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Archer rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Archer attacked";
            w->bah->selectedUnit->attackUnit(this);
        }
    }
}
