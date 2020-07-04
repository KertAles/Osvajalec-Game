#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include <QGraphicsItemGroup>

class UIComponent: public QGraphicsItemGroup
{
public:
    UIComponent();
    virtual void update() = 0;
};

#endif // UICOMPONENT_H
