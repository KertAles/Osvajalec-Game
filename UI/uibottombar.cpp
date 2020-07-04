#include "mainwindow.h"
#include "uibottombar.h"
#include "actionbutton.h"
#include "queueunit.h"
#include "queuebuilding.h"
#include "Units/worker.h"
#include "Buildings/fort.h"
#include "Buildings/farm.h"

#include <QDebug>

extern MainWindow* w;

UIBottomBar::UIBottomBar() {
    endTurnB = new ActionButton(100,100);

    attackB = new ActionButton(30, 30);
    destroyB = new ActionButton(30, 30);
    moveB = new ActionButton(30, 30);

    buildFaB = new ActionButton(50, 50);
    buildMiB = new ActionButton(50, 50);
    buildFB = new ActionButton(50, 50);
    buildWcB = new ActionButton(50, 50);

    makeArchB = new ActionButton(50, 50);
    makeKniB = new ActionButton(50, 50);
    makePikeB = new ActionButton(50, 50);
    makeWorB = new ActionButton(50, 50);

    queueButton = new ActionButton(50, 50);

    currentUnit = nullptr;
    currentBuilding = nullptr;
}

UIBottomBar::~UIBottomBar() {
    delete endTurnB;

    delete attackB;
    delete destroyB;
    delete moveB;

    delete buildFaB;
    delete buildMiB;
    delete buildFB;
    delete buildWcB;

    delete makeArchB;
    delete makeKniB;
    delete makePikeB;
    delete makeWorB;

    delete queueButton;
}

void UIBottomBar::init(float width, float height) {
    bar.setRect(0.0f, 0.0f, width, height);
    this->addToGroup(&bar);
    bar.setPos(0.0f, w->height()-height);

    hpLeft.setRect(0.0f, 0.0f, HPBARSIZE, HPBARHEIGHT);
    this->addToGroup(&hpLeft);
    hpLeft.setPos(50.0f, w->height() - height + 20.0f);
    hpLeft.setZValue(0.15f);

    hpMax.setRect(0.0f, 0.0f, HPBARSIZE, HPBARHEIGHT);
    this->addToGroup(&hpMax);
    hpMax.setPos(50.0f, w->height() - height + 20.0f);
    hpMax.setZValue(0.1f);

    hpText.setPos(50.f + HPBARSIZE/2, w->height() - height + 20.0f);
    hpText.setZValue(0.2f);
    this->addToGroup(&hpText);

    unitMode.setPos(170.0f, w->height() - height + 65.0f);
    this->addToGroup(&unitMode);

    movesLeft.setPos(170.0f, w->height() - height + 50.0f);
    this->addToGroup(&movesLeft);

    hpLeft.setVisible(false);
    hpMax.setVisible(false);
    hpText.setVisible(false);

    this->setHandlesChildEvents(false);

    hpLeft.setBrush(QBrush(Qt::green));
    hpMax.setBrush(QBrush(Qt::red));
    bar.setBrush(QBrush(Qt::white));

    endTurnB->setPixmap(QPixmap(":/images/Buttons/endTurn.png"));

    attackB->setPixmap(QPixmap(":/images/Buttons/attack.png"));
    destroyB->setPixmap(QPixmap(":/images/Buttons/destroy.png"));
    moveB->setPixmap(QPixmap(":/images/Buttons/move.png"));

    makeWorB->setPixmap(QPixmap(":/images/Buttons/makeWorker.png"));
    makeArchB->setPixmap(QPixmap(":/images/Buttons/makeArcher.png"));
    makeKniB->setPixmap(QPixmap(":/images/Buttons/makeKnight.png"));
    makePikeB->setPixmap(QPixmap(":/images/Buttons/makePikeman.png"));

    buildFaB->setPixmap(QPixmap(":/images/Buttons/makeFarm.png"));
    buildMiB->setPixmap(QPixmap(":/images/Buttons/makeMine.png"));
    buildFB->setPixmap(QPixmap(":/images/Buttons/makeFort.png"));
    buildWcB->setPixmap(QPixmap(":/images/Buttons/makeWoodcamp.png"));

    this->connect(endTurnB, SIGNAL(clicked()), this, SLOT(endTurnClicked()));

    this->connect(moveB, SIGNAL(clicked()), this, SLOT(moveClicked()));
    this->connect(destroyB, SIGNAL(clicked()), this, SLOT(destroyClicked()));
    this->connect(attackB, SIGNAL(clicked()), this, SLOT(attackClicked()));

    this -> connect(makeWorB, SIGNAL(clicked()), this, SLOT(makeWorkerClicked()));
    this -> connect(makeArchB, SIGNAL(clicked()), this, SLOT(makeArcherClicked()));
    this -> connect(makeKniB, SIGNAL(clicked()), this, SLOT(makeKnightClicked()));
    this -> connect(makePikeB, SIGNAL(clicked()), this, SLOT(makePikemanClicked()));

    this -> connect(buildFaB, SIGNAL(clicked()), this, SLOT(makeFarmClicked()));
    this -> connect(buildMiB, SIGNAL(clicked()), this, SLOT(makeMineClicked()));
    this -> connect(buildFB, SIGNAL(clicked()), this, SLOT(makeFortClicked()));
    this -> connect(buildWcB, SIGNAL(clicked()), this, SLOT(makeWoodcampClicked()));

    this -> connect(queueButton, SIGNAL(clicked()), this, SLOT(queueButtonClicked()));


    this->addToGroup(endTurnB);

    this->addToGroup(attackB);
    this->addToGroup(destroyB);
    this->addToGroup(moveB);

    this->addToGroup(makeWorB);
    this->addToGroup(makeArchB);
    this->addToGroup(makeKniB);
    this->addToGroup(makePikeB);

    this->addToGroup(buildFaB);
    this->addToGroup(buildMiB);
    this->addToGroup(buildFB);
    this->addToGroup(buildWcB);

    this->addToGroup(queueButton);

    endTurnB->setPos(w->width()-200.0f ,w->height()-height+30.0f);

    QFont playerFont = playerName.font();
    playerFont.setBold(true);
    playerFont.setPixelSize(16);
    playerName.setFont(playerFont);

    playerFont = currentPlayer.font();
    playerFont.setPixelSize(16);
    currentPlayer.setFont(playerFont);

    currentPlayer.setPlainText("Current player:");

    playerName.setPos(w->width()-200.0f, w->height()-height + 10.0f);
    this->addToGroup(&playerName);
    currentPlayer.setPos(playerName.x()-(currentPlayer.boundingRect().width()), w->height()-height + 10.0f);
    this->addToGroup(&currentPlayer);

    moveB->setPos(50.0f ,w->height()-height+50.0f);
    attackB->setPos(90.0f ,w->height()-height+50.0f);
    destroyB->setPos(130.0f ,w->height()-height+50.0f);

    makeArchB->setPos(50.0f ,w->height()-height+90.0f);
    makeKniB->setPos(110.0f ,w->height()-height+90.0f);
    makePikeB->setPos(170.0f ,w->height()-height+90.0f);
    makeWorB->setPos(230.0f ,w->height()-height+90.0f);

    buildFaB->setPos(50.0f ,w->height()-height+90.0f);
    buildMiB->setPos(50.0f ,w->height()-height+90.0f);
    buildWcB->setPos(50.0f ,w->height()-height+90.0f);
    buildFB->setPos(110.0f ,w->height()-height+90.0f);

    queueButton->setPos(50.f + HPBARSIZE + 20.0f, w->height() - height + 20.0f);
    turnsLeft.setPos(50.f + HPBARSIZE + 71.0f, w->height() - height + 50.0f);
    turnsLeft.setZValue(0.1f);
    this->addToGroup(&turnsLeft);

    makeArchB->setVisible(false);
    makeKniB->setVisible(false);
    makePikeB->setVisible(false);
    makeWorB->setVisible(false);

    buildFaB->setVisible(false);
    buildFB->setVisible(false);
    buildMiB->setVisible(false);
    buildWcB->setVisible(false);

    attackB->setVisible(false);
    moveB->setVisible(false);
    destroyB->setVisible(false);

    currentPlayer.setVisible(true);
    playerName.setVisible(true);
    endTurnB->setVisible(true);
}

void UIBottomBar::update() {
    this->refresh();
}

void UIBottomBar::refresh() {
    if(w->bah->localPlayer == w->bah->activePlayer) {
        this->inTurn();
        queueButton->disable(false);
    }
    else {
        this->outOfTurn();
        queueButton->disable(true);
    }
    currentPlayer.setPlainText("Current player: ");
    playerName.setPlainText(w->bah->activePlayer->getName());
    playerName.setDefaultTextColor(w->bah->activePlayer->getColour());
}

void UIBottomBar::inTurn() {
    if(currentUnit) {
        QRectF temp = hpLeft.rect();
        temp.setWidth(HPBARSIZE*((float)currentUnit->getHp()/(float)currentUnit->getMaxHp()));
        hpLeft.setRect(temp);
        hpText.setPlainText(QString::number(currentUnit->getHp()) + "/" + QString::number(currentUnit->getMaxHp()));
        hpText.setPos(50.f + HPBARSIZE/2 - hpText.boundingRect().width()/2, w->height() - bar.boundingRect().height() + 20.0f);

        if(currentUnit->getOwner() == w->bah->localPlayer) {
            movesLeft.setPlainText(QString::number(currentUnit->getMovesLeft(),'f',2) + "/" + QString::number(currentUnit->getMaxMoves(),'f',0));
            if(currentUnit->getType() == 'w') {
                Worker* tmp = (Worker*)currentUnit;
                if(tmp->getQueueItem()) {
                    queueButton->setVisible(true);
                    switch(tmp->getQueueItem()->getType()) {
                    case 'r': queueButton->setPixmap(QPixmap(":/images/Buttons/makeFort.png")); break;
                    case 'f': queueButton->setPixmap(QPixmap(":/images/Buttons/makeFarm.png")); break;
                    case 'm': queueButton->setPixmap(QPixmap(":/images/Buttons/makeMine.png")); break;
                    case 'w': queueButton->setPixmap(QPixmap(":/images/Buttons/makeWoodcamp.png")); break;
                    }
                    turnsLeft.setPlainText(QString::number(tmp->getQueueItem()->getTurnsLeft()));
                    turnsLeft.setVisible(true);
                }
                else {
                    queueButton->setVisible(false);
                    turnsLeft.setVisible(false);
                }
            }
            QString message = "Unit mode: ";
            switch(w->bah->unitOrderType) {
            case 'm': message += "Move"; break;
            case 'a': message += "Attack"; if(currentUnit->getMovesLeft()<=0) message+="(Not enough moves)"; break;
            default: message += "None";
            }
            unitMode.setPlainText(message);
        }
    }
    else if(currentBuilding) {
        QRectF temp = hpLeft.rect();
        temp.setWidth(HPBARSIZE*((float)currentBuilding->getHp()/(float)currentBuilding->getMaxHp()));
        hpLeft.setRect(temp);
        hpText.setPlainText(QString::number(currentBuilding->getHp()) + "/" + QString::number(currentBuilding->getMaxHp()));

        if(currentBuilding->getOwner() == w->bah->localPlayer) {
            if(currentBuilding->getType() == 'r' || currentBuilding->getType() == 'b') {
                if(currentBuilding->getQueueItem()) {
                    queueButton->setVisible(true);
                    switch(currentBuilding->getQueueItem()->getType()) {
                    case 'k': queueButton->setPixmap(QPixmap(":/images/Buttons/makeKnight.png")); break;
                    case 'p': queueButton->setPixmap(QPixmap(":/images/Buttons/makePikeman.png")); break;
                    case 'a': queueButton->setPixmap(QPixmap(":/images/Buttons/makeArcher.png")); break;
                    case 'w': queueButton->setPixmap(QPixmap(":/images/Buttons/makeWorker.png")); break;
                    }
                    turnsLeft.setPlainText(QString::number(currentBuilding->getQueueItem()->getTurnsLeft()));
                    turnsLeft.setVisible(true);
                }
                else {
                    queueButton->setVisible(false);
                    turnsLeft.setVisible(false);
                }
            }
        }
    }
}

void UIBottomBar::outOfTurn() {
    this->inTurn();
}

void UIBottomBar::workerButtons(Unit* actor) {
    currentUnit = actor;
    currentBuilding = nullptr;

    if(w->bah->localPlayer == w->bah->activePlayer) {
        QRectF temp = hpLeft.rect();
        temp.setWidth(HPBARSIZE*((float)actor->getHp()/(float)actor->getMaxHp()));
        hpLeft.setRect(temp);
        hpText.setPlainText(QString::number(actor->getHp()) + "/" + QString::number(actor->getMaxHp()));
        movesLeft.setPlainText(QString::number(actor->getMovesLeft()) + "/" + QString::number(actor->getMaxMoves()));

        hpLeft.setVisible(true);
        hpMax.setVisible(true);
        hpText.setVisible(true);
        movesLeft.setVisible(true);
        unitMode.setVisible(true);

        makeArchB->setVisible(false);
        makeKniB->setVisible(false);
        makePikeB->setVisible(false);
        makeWorB->setVisible(false);

        if(!(actor->getPosition()->getBuilding())) {
            if(improvementResCheck()) {
                buildFaB->disable(false);
                buildMiB->disable(false);
                buildWcB->disable(false);
            }
            else {
                buildFaB->disable(true);
                buildMiB->disable(true);
                buildWcB->disable(false);
            }

            if(fortResCheck())
                buildFB->disable(false);
            else
                buildFB->disable(true);

            if(!(actor->getPosition()->getOwner() == actor->getOwner())) {
                buildFaB->disable(true);
                buildMiB->disable(true);
                buildWcB->disable(true);
            }

            buildFB->setVisible(true);
            buildFaB->setVisible(false);
            buildMiB->setVisible(false);
            buildWcB->setVisible(false);

            switch(actor->getPosition()->getResource()->getType()) {
            case 'f': buildFaB->setVisible(true); break;
            case 'w': buildWcB->setVisible(true); break;
            case 'i': buildMiB->setVisible(true); break;
            case 'g': buildMiB->setVisible(true); break;
            }
        }
        else {
            buildFB->setVisible(false);
            buildFaB->setVisible(false);
            buildMiB->setVisible(false);
            buildWcB->setVisible(false);
        }

        attackB->setVisible(true);
        moveB->setVisible(true);
        destroyB->setVisible(true);

        Worker* tmp = (Worker*)actor;
        if(tmp->getQueueItem()) {
            queueButton->setVisible(true);
            switch(tmp->getQueueItem()->getType()) {
            case 'r': queueButton->setPixmap(QPixmap(":/images/Buttons/makeFort.png")); break;
            case 'f': queueButton->setPixmap(QPixmap(":/images/Buttons/makeFarm.png")); break;
            case 'm': queueButton->setPixmap(QPixmap(":/images/Buttons/makeMine.png")); break;
            case 'w': queueButton->setPixmap(QPixmap(":/images/Buttons/makeWoodcamp.png")); break;
            }
            turnsLeft.setPlainText(QString::number(tmp->getQueueItem()->getTurnsLeft()));
            turnsLeft.setVisible(true);
        }
        else {
            queueButton->setVisible(false);
            turnsLeft.setVisible(false);
        }
    }
    else
        this->enemyUnitButtons(actor);
}

void UIBottomBar::soldierButtons(Unit* actor) {
    currentUnit = actor;
    currentBuilding = nullptr;

    if(w->bah->localPlayer == w->bah->activePlayer) {
        QRectF temp = hpLeft.rect();
        temp.setWidth(HPBARSIZE*((float)actor->getHp()/(float)actor->getMaxHp()));
        hpLeft.setRect(temp);
        hpText.setPlainText(QString::number(actor->getHp()) + "/" + QString::number(actor->getMaxHp()));
        movesLeft.setPlainText(QString::number(actor->getMovesLeft()) + "/" + QString::number(actor->getMaxMoves()));

        hpLeft.setVisible(true);
        hpMax.setVisible(true);
        hpText.setVisible(true);
        movesLeft.setVisible(true);
        unitMode.setVisible(true);

        makeArchB->setVisible(false);
        makeKniB->setVisible(false);
        makePikeB->setVisible(false);
        makeWorB->setVisible(false);

        buildFaB->setVisible(false);
        buildFB->setVisible(false);
        buildMiB->setVisible(false);
        buildWcB->setVisible(false);

        attackB->setVisible(true);
        moveB->setVisible(true);
        destroyB->setVisible(true);

        queueButton->setVisible(false);
        turnsLeft.setVisible(false);
    }
    else
        this->enemyUnitButtons(actor);
}

void UIBottomBar::fortButtons(Building* actor) {
    if(w->bah->localPlayer == w->bah->activePlayer) {
        baseButtons(actor);
        makeWorB->setVisible(false);
        destroyB->setVisible(true);
    }
    else {
        currentUnit = nullptr;
        currentBuilding = actor;
        this->enemyBuildingButtons(actor);
    }

}

void UIBottomBar::baseButtons(Building* actor) {
    currentUnit = nullptr;
    currentBuilding = actor;

    if(w->bah->localPlayer == w->bah->activePlayer) {
        QRectF temp = hpLeft.rect();
        temp.setWidth(HPBARSIZE*((float)actor->getHp()/(float)actor->getMaxHp()));
        hpLeft.setRect(temp);
        hpText.setPlainText(QString::number(actor->getHp()) + "/" + QString::number(actor->getMaxHp()));

        hpLeft.setVisible(true);
        hpMax.setVisible(true);
        hpText.setVisible(true);
        movesLeft.setVisible(false);
        unitMode.setVisible(false);

        if(!(actor->getPosition()->getUnit())) {
            if(archerResCheck())
                makeArchB->disable(false);
            else
                makeArchB->disable(true);

            if(knightResCheck())
                makeKniB->disable(false);
            else
                makeKniB->disable(true);

            if(pikeResCheck())
                makePikeB->disable(false);
            else
                makePikeB->disable(true);

            if(workerResCheck())
                makeWorB->disable(false);
            else
                makeWorB->disable(true);
        }
        else {
            makeKniB->disable(true);
            makePikeB->disable(true);
            makeArchB->disable(true);
            makeWorB->disable(true);
        }

        makeArchB->setVisible(true);
        makeKniB->setVisible(true);
        makePikeB->setVisible(true);
        makeWorB->setVisible(true);

        buildFaB->setVisible(false);
        buildFB->setVisible(false);
        buildMiB->setVisible(false);
        buildWcB->setVisible(false);

        attackB->setVisible(false);
        moveB->setVisible(false);
        destroyB->setVisible(false);

        if(actor->getQueueItem()) {
            queueButton->setVisible(true);
            switch(actor->getQueueItem()->getType()) {
            case 'k': queueButton->setPixmap(QPixmap(":/images/Buttons/makeKnight.png")); break;
            case 'p': queueButton->setPixmap(QPixmap(":/images/Buttons/makePikeman.png")); break;
            case 'a': queueButton->setPixmap(QPixmap(":/images/Buttons/makeArcher.png")); break;
            case 'w': queueButton->setPixmap(QPixmap(":/images/Buttons/makeWorker.png")); break;
            }
            turnsLeft.setPlainText(QString::number(actor->getQueueItem()->getTurnsLeft()));
            turnsLeft.setVisible(true);
        }
        else {
            queueButton->setVisible(false);
            turnsLeft.setVisible(false);
        }
    }
    else
        this->enemyBuildingButtons(actor);
}

void UIBottomBar::buildingButtons(Building* actor) {
    currentUnit = nullptr;
    currentBuilding = actor;

    if(w->bah->localPlayer == w->bah->activePlayer) {
        QRectF temp = hpLeft.rect();
        temp.setWidth(HPBARSIZE*((float)actor->getHp()/(float)actor->getMaxHp()));
        hpLeft.setRect(temp);
        hpText.setPlainText(QString::number(actor->getHp()) + "/" + QString::number(actor->getMaxHp()));

        hpLeft.setVisible(true);
        hpMax.setVisible(true);
        hpText.setVisible(true);
        movesLeft.setVisible(false);
        unitMode.setVisible(false);

        makeArchB->setVisible(false);
        makeKniB->setVisible(false);
        makePikeB->setVisible(false);
        makeWorB->setVisible(false);

        buildFaB->setVisible(false);
        buildFB->setVisible(false);
        buildMiB->setVisible(false);
        buildWcB->setVisible(false);

        attackB->setVisible(false);
        moveB->setVisible(false);
        destroyB->setVisible(true);

        queueButton->setVisible(false);
        turnsLeft.setVisible(false);
    }
    else
        this->enemyBuildingButtons(actor);
}

void UIBottomBar::enemyUnitButtons(Unit* actor) {
    currentUnit = actor;
    currentBuilding = nullptr;

    QRectF temp = hpLeft.rect();
    temp.setWidth(HPBARSIZE*((float)actor->getHp()/(float)actor->getMaxHp()));
    hpLeft.setRect(temp);
    hpText.setPlainText(QString::number(actor->getHp()) + "/" + QString::number(actor->getMaxHp()));

    hpLeft.setVisible(true);
    hpMax.setVisible(true);
    hpText.setVisible(true);
    movesLeft.setVisible(false);
    unitMode.setVisible(false);

    makeArchB->setVisible(false);
    makeKniB->setVisible(false);
    makePikeB->setVisible(false);
    makeWorB->setVisible(false);

    buildFaB->setVisible(false);
    buildFB->setVisible(false);
    buildMiB->setVisible(false);
    buildWcB->setVisible(false);

    attackB->setVisible(false);
    moveB->setVisible(false);
    destroyB->setVisible(false);

    queueButton->setVisible(false);
    turnsLeft.setVisible(false);
}

void UIBottomBar::enemyBuildingButtons(Building* actor) {
    currentUnit = nullptr;
    currentBuilding = actor;

    QRectF temp = hpLeft.rect();
    temp.setWidth(HPBARSIZE*((float)actor->getHp()/(float)actor->getMaxHp()));
    hpLeft.setRect(temp);
    hpText.setPlainText(QString::number(actor->getHp()) + "/" + QString::number(actor->getMaxHp()));

    hpLeft.setVisible(true);
    hpMax.setVisible(true);
    hpText.setVisible(true);
    movesLeft.setVisible(false);
    unitMode.setVisible(false);

    makeArchB->setVisible(false);
    makeKniB->setVisible(false);
    makePikeB->setVisible(false);
    makeWorB->setVisible(false);

    buildFaB->setVisible(false);
    buildFB->setVisible(false);
    buildMiB->setVisible(false);
    buildWcB->setVisible(false);

    attackB->setVisible(false);
    moveB->setVisible(false);
    destroyB->setVisible(false);

    queueButton->setVisible(false);
    turnsLeft.setVisible(false);
}

void UIBottomBar::clearButtons() {
    currentUnit = nullptr;
    currentBuilding = nullptr;

    hpLeft.setVisible(false);
    hpMax.setVisible(false);
    hpText.setVisible(false);
    movesLeft.setVisible(false);
    unitMode.setVisible(false);

    makeArchB->setVisible(false);
    makeKniB->setVisible(false);
    makePikeB->setVisible(false);
    makeWorB->setVisible(false);

    buildFaB->setVisible(false);
    buildFB->setVisible(false);
    buildMiB->setVisible(false);
    buildWcB->setVisible(false);

    attackB->setVisible(false);
    moveB->setVisible(false);
    destroyB->setVisible(false);

    queueButton->setVisible(false);
    turnsLeft.setVisible(false);
}

void UIBottomBar::moveClicked() {
    qDebug() << "Move clicked";
    w->bah->unitOrderType = 'm';
}

void UIBottomBar::attackClicked() {
    qDebug() << "Attack clicked";
    w->bah->unitOrderType = 'a';
}

void UIBottomBar::destroyClicked() {
    qDebug() << "Destroy clicked";
    //TODO:: are you sure?
    if(w->bah->selectedBuilding) {
        delete w->bah->selectedBuilding;
        w->bah->selectedBuilding = nullptr;
        currentBuilding = nullptr;
    }
    else if(w->bah->selectedUnit) {
        delete w->bah->selectedUnit;
        w->bah->selectedUnit = nullptr;
        currentUnit = nullptr;
    }
}

void UIBottomBar::endTurnClicked() {
    if(w->bah->localPlayer == w->bah->activePlayer) {
         qDebug() << "End turn clicked";
         w->bah->nextPlayer();
    }
}


void UIBottomBar::makeArcherClicked() {
    if( !(makeArchB->isDisabled())) {
            new QueueUnit('a', w->bah->selectedBuilding);
            w->bah->updateTopBar();

            qDebug() << "Archer added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::makeKnightClicked() {
    if( !(makeKniB->isDisabled())) {
            new QueueUnit('k', w->bah->selectedBuilding);
            w->bah->updateTopBar();

            qDebug() << "Knight added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::makePikemanClicked() {
    if( !(makePikeB->isDisabled())) {
            new QueueUnit('p', w->bah->selectedBuilding);
            w->bah->updateTopBar();

            qDebug() << "Pikeman added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::makeWorkerClicked() {
    if( !(makeWorB->isDisabled())) {
            new QueueUnit('w', w->bah->selectedBuilding);
            w->bah->updateTopBar();

            qDebug() << "Worker added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::makeFortClicked() {
    if( !(buildFB->isDisabled())) {
        new QueueBuilding('r', (Worker*)w->bah->selectedUnit);
        w->bah->updateTopBar();

        qDebug() << "Fort added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::makeFarmClicked() {
    if( !(buildFaB->isDisabled())) {
        new QueueBuilding('f', (Worker*)w->bah->selectedUnit);

        w->bah->updateTopBar();

        qDebug() << "Farm added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::makeMineClicked() {
    if( !(buildMiB->isDisabled())) {
        new QueueBuilding('m', (Worker*)w->bah->selectedUnit);
        w->bah->updateTopBar();

        qDebug() << "Mine added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::makeWoodcampClicked() {
    if( !(buildWcB->isDisabled())) {
        new QueueBuilding('w', (Worker*)w->bah->selectedUnit);
        w->bah->updateTopBar();

        qDebug() << "Woodcamp added to queue";
    }
    else
        qDebug() << "Button disabled";
}

void UIBottomBar::queueButtonClicked() {
    if(!queueButton->isDisabled()) {
        if(currentUnit) {
            Worker* tmp = (Worker*) currentUnit;
            tmp->undoQueueItem();
        }
        else if(currentBuilding) {
            currentBuilding->undoQueueItem();
        }
    }
}

bool UIBottomBar::workerResCheck() {
    bool valid = false;
    Stockpile stock = w->bah->selectedBuilding->getOwner()->getStockpile();

    if(stock.getFood() >= 1) {
        valid = true;
    }

    return valid;
}

bool UIBottomBar::pikeResCheck() {
    bool valid = false;
    Stockpile stock = w->bah->selectedBuilding->getOwner()->getStockpile();

    if(stock.getFood() >= 1 && stock.getWood() >= 1) {
        valid = true;
    }

    return valid;
}

bool UIBottomBar::knightResCheck() {
    bool valid = false;
    Stockpile stock = w->bah->selectedBuilding->getOwner()->getStockpile();

    if(stock.getFood() >= 1 && stock.getIron() >= 1) {
        valid = true;
    }

    return valid;
}

bool UIBottomBar::archerResCheck() {
    bool valid = false;
    Stockpile stock = w->bah->selectedBuilding->getOwner()->getStockpile();

    if(stock.getFood() >= 1 && stock.getWood() >= 1) {
        valid = true;
    }

    return valid;
}

bool UIBottomBar::fortResCheck() {
    bool valid = false;
    Stockpile stock = w->bah->selectedUnit->getOwner()->getStockpile();

    if(stock.getWood() >= 5 && stock.getIron() >= 3 && stock.getGold() >= 2) {
        valid = true;
    }

    return valid;
}

bool UIBottomBar::improvementResCheck() {
    bool valid = false;
    Stockpile stock = w->bah->selectedUnit->getOwner()->getStockpile();

    if(stock.getWood() >= 1) {
        valid = true;
    }

    return valid;
}
