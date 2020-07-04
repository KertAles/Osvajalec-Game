#include "victoryscreen.h"
#include "mainwindow.h"

extern MainWindow* w;

VictoryScreen::VictoryScreen() {
    exit = new MainMenuButton;
}

VictoryScreen::~VictoryScreen() {
    if(exit)
        delete exit;
}

void VictoryScreen::init(Player* winner) {
    float buttonSize = 300.0f;

    exit->setRect(0.0f, 0.0f, buttonSize, 100.0f);

    exit->setBrush(QBrush(QColor(255, 107, 107)));

    this->connect(exit, SIGNAL(clicked()), this, SLOT(exitClicked()));

    QFont font;
    if(winner) {
        font = playerName.font();
        font.setPixelSize(60);
        font.setBold(true);
        playerName.setFont(font);
        playerName.setDefaultTextColor(winner->getColour());
        playerName.setPlainText(winner->getName());
    }
    else {
        playerName.setPlainText("Nekje se je zalomilo.");
    }
    victoryText.setPlainText("Zmagal je");
    exitText.setPlainText("EXIT");

    font = victoryText.font();
    font.setPixelSize(60);
    victoryText.setFont(font);
    exitText.setFont(font);

    victoryText.setPos(this->width()/2 - victoryText.boundingRect().width()/2, 210.0f);
    playerName.setPos(this->width()/2 - playerName.boundingRect().width()/2, 290.0f);
    exit->setPos((this->width()/2 - buttonSize/2), 400.0f);
    exitText.setPos(this->width()/2 - exitText.boundingRect().width()/2, 410.0f );

    this->addItem(&victoryText);
    this->addItem(&playerName);
    this->addItem(exit);
    this->addItem(&exitText);
}

void VictoryScreen::exitClicked() {
    w->close();
}
