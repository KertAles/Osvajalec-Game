#ifndef RESOURCE_H
#define RESOURCE_H

#include <QGraphicsItem>
#include <QPen>

class GridSquare;

class Resource : public QGraphicsItemGroup
{
    char type; // w - wood; f - food; i - iron; g - gold; n - none
    int amount;
    QGraphicsEllipseItem* resourceEllipse;
    QGraphicsPixmapItem* amountText;
    bool exploited;
    bool disabled;

    QPen defPen;
public:
    Resource();
    ~Resource();

    char getType();
    int getAmount();
    void exploit(bool status);
    bool isExploited();
    bool isDisabled() { return disabled; }
    void disableResource();
    void enableResource();

    void generateResource(GridSquare* currentSquare);
    void rollPlains(int dice);
    void rollWoods(int dice);
    void rollHills(int dice);
    void rollMountains(int dice);
    void reloadResourcePixmaps();
    void addToScene();
    void hideResource();
    void setPosition(int x, int y);
    void reveal();

signals:

public slots:
};

#endif // RESOURCE_H
