#ifndef UITOPBAR_H
#define UITOPBAR_H

#include "player.h"
#include "uicomponent.h"
#include "actionbutton.h"

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class UITopBar: public UIComponent
{
    QGraphicsRectItem bar;

    ActionButton* menuB;

    QGraphicsPixmapItem foodIcon;
    QGraphicsPixmapItem woodIcon;
    QGraphicsPixmapItem ironIcon;
    QGraphicsPixmapItem goldIcon;

    QGraphicsTextItem foodData;
    QGraphicsTextItem woodData;
    QGraphicsTextItem ironData;
    QGraphicsTextItem goldData;
public:
    UITopBar();
    ~UITopBar();

    void init(float width, float height);
    void update();
    void updateResData(Player* player);
};

#endif // UITOPBAR_H
