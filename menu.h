#ifndef MENU_H
#define MENU_H

#include "Buttons/mainmenubutton.h"

#include <QGraphicsScene>
#include <QGraphicsTextItem>

class Menu : public QGraphicsScene
{
    Q_OBJECT

    MainMenuButton* play;
    MainMenuButton* exit;

    QGraphicsTextItem playText;
    QGraphicsTextItem exitText;
public:
    Menu();
    ~Menu();

    void init();
public slots:
    void playClicked();
    void exitClicked();
};

#endif // MENU_H
