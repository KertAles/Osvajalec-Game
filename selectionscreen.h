#ifndef SELECTIONSCREEN_H
#define SELECTIONSCREEN_H

#include "Buttons/mainmenubutton.h"

#include <QGraphicsScene>
#include <QLineEdit>
#include <QComboBox>

class SelectionScreen : public QGraphicsScene
{
    Q_OBJECT

    QGraphicsRectItem p1Colour;
    QGraphicsRectItem p2Colour;
    QGraphicsRectItem p3Colour;
    QGraphicsRectItem p4Colour;

    QLineEdit p1Name;
    QLineEdit p2Name;
    QLineEdit p3Name;
    QLineEdit p4Name;

    QComboBox sizeCombo;
    QComboBox modeCombo;

    MainMenuButton* startGame;
    QGraphicsTextItem startText;
    QGraphicsTextItem errorMessage;
public:
    SelectionScreen();

    void init();
signals:

public slots:
    void startClicked();
};

#endif // SELECTIONSCREEN_H
