#ifndef MAINMENUBUTTON_H
#define MAINMENUBUTTON_H

#include <QGraphicsPixmapItem>

class MainMenuButton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    MainMenuButton();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void clicked();
public slots:
};

#endif // MAINMENUBUTTON_H
