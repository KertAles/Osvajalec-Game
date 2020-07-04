#ifndef VICTORYSCREEN_H
#define VICTORYSCREEN_H

#include "Buttons/mainmenubutton.h"
#include "player.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>

class VictoryScreen : public QGraphicsScene
{
    Q_OBJECT

    QGraphicsTextItem victoryText;
    QGraphicsTextItem playerName;
    MainMenuButton* exit;
    QGraphicsTextItem exitText;
public:
    VictoryScreen();
    ~VictoryScreen();

    void init(Player* winner);
public slots:
    void exitClicked();
};

#endif // VICTORYSCREEN_H
