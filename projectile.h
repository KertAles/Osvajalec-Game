#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "unit.h"
#include "building.h"

class Projectile : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Projectile();
    void launchArrow(Unit* source, Unit* dest);
    void launchArrow(Unit* source, Building* dest);
    void launchArrow(Building* source, Unit* dest);
    void launchBoulder(Building* source, Unit* dest);
    void launch(QPointF source, QPointF dest);
signals:

public slots:
};

#endif // PROJECTILE_H
