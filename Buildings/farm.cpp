#include "farm.h"

extern MainWindow* w;

Farm::Farm(Player* ownedBy, GridSquare* createPos) {
    owner = ownedBy;
    position = createPos;
    type = 'f';

    blocksMovement = false;
    maxHp = 50;
    hp = maxHp;
    defense = 0;
    los = 2;
    areaOfInfluence = -1;

    queueItem = nullptr;

    this->setPos(position->getX() + 7, position->getY()+SQUARESIZE - (BUILDINGSIZE + 8));
    this->init();
    buildPix->setPixmap(QPixmap(":/images/Buildings/farm.png"));
    w->bah->addItem(this);

    position->setBuilding(this);
    position->getResource()->exploit(true);
    owner -> addBuilding(this);
    owner -> updateIncome();
    qDebug() << "Farm created";
}

Farm::~Farm() {
    if(w->bah->selectedBuilding == this) {
        w->bah->selectedBuilding = nullptr;
        w->bah->clearButtons();
    }
    if(queueItem)
        delete queueItem;
    position->building = nullptr;
    position -> getResource() -> exploit(false);
    owner -> removeBuilding(this);
    owner -> updateIncome();

    delete buildPix;
    delete background;
}

void Farm::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Farm leftclicked";
        w->bah->selectedBuilding = this;
        w->bah->selectedUnit = nullptr;
        w->bah->unitOrderType = 'k';

        if(this->getOwner() == w->bah->localPlayer)
            w->bah->buildingButtons(this);
        else
            w->bah->enemyBuildingButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Farm rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Farm attacked";
            w->bah->selectedUnit->attackBuilding(this);
        }
    }
}
