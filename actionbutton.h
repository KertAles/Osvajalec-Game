#ifndef ACTIONBUTTON_H
#define ACTIONBUTTON_H

#include "mainwindow.h"

#include <QGraphicsPixmapItem>

class ActionButton : public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT
     bool disabled;
     float sizeX;
     float sizeY;
public:
    ActionButton(float x, float y);

    void disable(bool dis) { disabled = dis; }
    bool isDisabled() { return disabled; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
};

#endif // ACTIONBUTTON_H
