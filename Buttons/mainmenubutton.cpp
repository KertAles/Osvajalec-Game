#include "mainmenubutton.h"

#include <QGraphicsSceneMouseEvent>

MainMenuButton::MainMenuButton()
{

}

void MainMenuButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();
    emit clicked();
}

