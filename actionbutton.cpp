#include "actionbutton.h"

ActionButton::ActionButton(float x, float y) {
    sizeX = x;
    sizeY = y;
    disabled = false;
}
void ActionButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter,option,widget);
    if(disabled) {
        painter->setBrush(QBrush(QColor(50,50,50,190)));
        painter->drawRect(0.0f, 0.0f, sizeX, sizeY);
    }
}

void ActionButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    event->accept();
    emit clicked();
}
