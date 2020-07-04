#include "mine.h"

extern MainWindow* w;

Mine::Mine(Player* ownedBy, GridSquare* createPos) {
    owner = ownedBy;
    position = createPos;
    type = 'm';

    blocksMovement = false;
    maxHp = 50;
    hp = maxHp;
    defense = 0;
    los = 2;
    areaOfInfluence = -1;

    queueItem = nullptr;

    this->setPos(position->getX() + 7, position->getY()+SQUARESIZE - (BUILDINGSIZE + 8));
    this->init();
    buildPix->setPixmap(QPixmap(":/images/Buildings/mine.png"));
    w->bah->addItem(this);

    position->setBuilding(this);
    position->getResource()->exploit(true);
    owner -> addBuilding(this);
    owner -> updateIncome();
    qDebug() << "Mine created";
}

Mine::~Mine() {
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

void Mine::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Mine leftclicked";
        w->bah->selectedBuilding = this;
        w->bah->selectedUnit = nullptr;
        w->bah->unitOrderType = 'k';

        if(this->getOwner() == w->bah->localPlayer)
            w->bah->buildingButtons(this);
        else
            w->bah->enemyBuildingButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Mine rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Mine attacked";
            w->bah->selectedUnit->attackBuilding(this);
        }
    }
}
