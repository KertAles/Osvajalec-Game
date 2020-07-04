#ifndef GAME_H
#define GAME_H

#include "gridsquare.h"
#include "UI\uimanager.h"
#include "queueitem.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QVector>

class Player;
class Unit;
class Building;
class QueueItem;
class UITopBar;
class UIBottomBar;

class Game: public QGraphicsScene
{
    Q_OBJECT

    QTimer gameLoopTimer;
    int gridX;
    int gridY;
    QPoint currentMousePos;

    QList<Player*> players;

    UIManager uiManager;
    UITopBar* topBar;
    UIBottomBar* bottomBar;

    void wheelEvent(QGraphicsSceneWheelEvent *event);
public slots:
    void gameLoop();

public:
    bool destroying;
    bool gameOver;
    char mode;

    QVector< QVector<GridSquare*> > grid;
    QList<QueueItem*> queue;

    Player* localPlayer;
    Player* activePlayer;
    Unit* selectedUnit;
    Building* selectedBuilding;
    char unitOrderType;

    Game();
    ~Game();

    int getGridX();
    int getGridY();
    GridSquare* getSquare(int xPos, int yPos) { return grid[xPos][yPos]; }
    Player* getFirstPlayer() { return players.first(); }
    QList<Player*> getPlayers() { return players; }

    void init(QList<Player*> playerList, int sizeX, int sizeY, char moud);
    void updateCurrentMousePos(QPoint point);
    void updatePosition();
    void updateTopBar();
    void generateTerrain(bool first);
    char decideTerrain(int i, int j);
    bool checkMapValidity(int numOfPlayers);
    void addQueueItem(QueueItem* item);
    void removeQueueItem(QueueItem* item);
    void removePlayer(Player* player);
    void setFoW(int i, int j, bool stat);

    void nextPlayer();
    void countdown(Player* player);
    void checkForWinner();

    void workerButtons(Unit* actor);
    void soldierButtons(Unit* actor);
    void fortButtons(Building* actor);
    void baseButtons(Building* actor);
    void buildingButtons(Building* actor);
    void enemyUnitButtons(Unit* actor);
    void enemyBuildingButtons(Building* actor);
    void clearButtons();

    void test();

signals:

public slots:
};

#endif // GAME_H
