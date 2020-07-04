#include "base.h"

extern MainWindow* w;

Base::Base(Player* ownedBy, GridSquare* createPos)
{
    owner = ownedBy;
    position = createPos;
    type = 'b';

    blocksMovement = true;
    maxHp = 1000; //1000
    hp = maxHp;
    defense = 125;
    los = 4;
    areaOfInfluence = 2;

    queueItem = nullptr;

    this->setPos(position->getX() + 7, position->getY()+SQUARESIZE - (BUILDINGSIZE + 8));
    this->init();
    buildPix->setPixmap(QPixmap(":/images/Buildings/base.png"));
    w->bah->addItem(this);

    position->setBuilding(this);
    position->getResource()->disableResource();
    owner -> addBuilding(this);

    InfluenceCalculator::calculateInfluence();
    qDebug() << "Base created";
}

Base::~Base() {

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

void Base::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();

    if(event->button() == Qt::LeftButton) {
        qDebug() << "Base leftclicked";
        w->bah->selectedBuilding = this;
        w->bah->selectedUnit = nullptr;
        w->bah->unitOrderType = 'k';

        if(this->getOwner() == w->bah->localPlayer)
            w->bah->baseButtons(this);
        else
            w->bah->enemyBuildingButtons(this);
    }
    else if(event->button() == Qt::RightButton) {
        qDebug() << "Base rightclicked";
        if(w->bah->selectedUnit != nullptr && w->bah->unitOrderType == 'a') {
            qDebug() << "Base attacked";
            w->bah->selectedUnit->attackBuilding(this);
        }
    }
}
