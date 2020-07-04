#ifndef UIBOTTOMBAR_H
#define UIBOTTOMBAR_H

#include "unit.h"
#include "uicomponent.h"

#include <QGraphicsRectItem>

class Unit;

class ActionButton;

class UIBottomBar : public QObject, public UIComponent
{
    Q_OBJECT

    QGraphicsRectItem bar;

    QGraphicsRectItem hpLeft;
    QGraphicsRectItem hpMax;
    QGraphicsTextItem hpText;

    QGraphicsTextItem movesLeft;

    QGraphicsTextItem unitMode;

    ActionButton* queueButton;
    QGraphicsTextItem turnsLeft;

    ActionButton* endTurnB;
    QGraphicsTextItem currentPlayer;
    QGraphicsTextItem playerName;

    ActionButton* attackB;
    ActionButton* destroyB;
    ActionButton* moveB;

    ActionButton* buildFaB;
    ActionButton* buildMiB;
    ActionButton* buildFB;
    ActionButton* buildWcB;

    ActionButton* makeArchB;
    ActionButton* makeKniB;
    ActionButton* makePikeB;
    ActionButton* makeWorB;

    Unit* currentUnit;
    Building* currentBuilding;
public:
    UIBottomBar();
    ~UIBottomBar();
    void init(float width, float height);
    void refresh();
    void update();

    void inTurn();
    void outOfTurn();
    void clearCurrentUnit() { currentUnit = nullptr; currentBuilding = nullptr; }
    void workerButtons(Unit* actor);
    void soldierButtons(Unit* actor);
    void fortButtons(Building* actor);
    void baseButtons(Building* actor);
    void buildingButtons(Building* actor);
    void enemyUnitButtons(Unit* actor);
    void enemyBuildingButtons(Building* actor);

    bool workerResCheck();
    bool pikeResCheck();
    bool knightResCheck();
    bool archerResCheck();
    bool fortResCheck();
    bool improvementResCheck();

    void clearButtons();

public slots:
    void endTurnClicked();

    void moveClicked();
    void attackClicked();
    void destroyClicked();

    void makeArcherClicked();
    void makeKnightClicked();
    void makePikemanClicked();
    void makeWorkerClicked();

    void makeFortClicked();
    void makeFarmClicked();
    void makeMineClicked();
    void makeWoodcampClicked();

    void queueButtonClicked();
};

#endif // UIBOTTOMBAR_H
