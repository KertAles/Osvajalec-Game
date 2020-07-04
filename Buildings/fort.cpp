#include "fort.h"

extern MainWindow* w;

Fort::Fort(Player* ownedBy, GridSquare* createPos) {
    owner = ownedBy;
    position = createPos;
    type = 'r';

    blocksMovement = true;
    maxHp = 500;
    hp = maxHp;
    defense = 50;
    los = 3;
    areaOfInfluence = 2;

    queueItem = nullptr;

    this->setPos(position->getX() + 7, position->getY()+SQUARESIZE - (BUILDINGSIZE + 8));
    this->init();
    buildPix->setPixmap(QPixmap(":/images/Buildings/fort.png"));
    w->bah->addItem(this);

    position->setBuilding(this);
    position->getResource()->disableResource();
    owner -> addBuilding(this);
    owner -> updateIncome();

    InfluenceCalculator::calculateInfluence();
    qDebug() << "Fort created";
}

Fort::~Fort() {
    if(w->bah->selectedBuilding == this) {
        w->bah->selectedBuilding = nullptr;
        w->bah->clearButtons();
    }
    if(queueItem)
        delete queueItem;
    position->getResource()->enableResource();
    position->building = nullptr;
    owner -> removeBuilding(this);

    if(!w->bah->destroying)
        InfluenceCalculator::calculateInfluence();

    delete buildPix;
    delete background;
}

void Fort::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Fort leftclicked";
        w->bah->selectedBuilding = this;
        w->bah->selectedUnit = nullptr;
        w->bah->unitOrderType = 'k';

        if(this->getOwner() == w->bah->localPlayer)
            w->bah->fortButtons(this);
        else
            w->bah->enemyBuildingButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Fort rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Fort attacked";
            w->bah->selectedUnit->attackBuilding(this);
        }
    }
}
