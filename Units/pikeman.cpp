#include "mainwindow.h"
#include "pikeman.h"

extern MainWindow* w;

Pikeman::Pikeman(Player* ownedBy, GridSquare* createPos) {
    owner = ownedBy;
    position = createPos;
    type = 'p';

    maxHp = 400;
    hp = maxHp;
    attack = 125;
    defense = 200;
    range = 1;
    los = 2;

    upkeep.setResource('w');
    upkeep.setAmount(1);

    maxMoves = 3;
    movesLeft = maxMoves;

    this->setPos(position->getX()+SQUARESIZE -(UNITSIZE + 7), position->getY() + 6);
    this->init();
    unitPix -> setPixmap(QPixmap(":/images/Units/pikeman.png"));
    w->bah->addItem(this);

    position->setUnit(this);
    owner -> addUnit(this);
    owner -> updateIncome();
    qDebug() << "Pikeman created";
}

Pikeman::~Pikeman() {
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

void Pikeman::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Pikeman leftclicked";
        w->bah->selectedBuilding = nullptr;
        w->bah->selectedUnit = this;
        w->bah->unitOrderType = 'm';

        if(this->getOwner() == w->bah->localPlayer)
            w->bah->soldierButtons(this);
        else
            w->bah->enemyUnitButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Pikeman rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Pikeman attacked";
            w->bah->selectedUnit->attackUnit(this);
        }
    }
}
