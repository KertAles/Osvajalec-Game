#ifndef RESOURCETEXT_H
#define RESOURCETEXT_H

#include <QGraphicsTextItem>

class ResourceText : public QGraphicsTextItem
{
public:
    ResourceText();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:

public slots:
};

#endif // RESOURCETEXT_H
