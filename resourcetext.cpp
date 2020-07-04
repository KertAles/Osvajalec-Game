#include "resourcetext.h"

#include <QPainter>

ResourceText::ResourceText()
{

}

void ResourceText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsTextItem::paint(painter,option,widget);
}
