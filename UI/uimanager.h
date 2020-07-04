#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <QList>
#include <QGraphicsItemGroup>

class UIComponent;

class UIManager: public QGraphicsItemGroup
{

    QList<UIComponent*> components;
public:
    UIManager();
    void update();
    void addComponent(UIComponent* newComponent);
signals:

public slots:
};

#endif // UIMANAGER_H
