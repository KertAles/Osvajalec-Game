#include "mainwindow.h"
#include "menu.h"

extern MainWindow* w;

Menu::Menu() {
    play = new MainMenuButton;
    exit = new MainMenuButton;
}

Menu::~Menu() {
    if(play)
        delete play;
    if(exit)
        delete exit;
}

void Menu::init() {
    float buttonSize = 300.0f;

    play->setRect(0.0f, 0.0f, buttonSize, 100.0f);
    exit->setRect(0.0f, 0.0f, buttonSize, 100.0f);

    play->setPos((this->width()/2 - buttonSize/2), 250.0f);
    exit->setPos((this->width()/2 - buttonSize/2), 400.0f);

    play->setBrush(QBrush(QColor(150, 255, 145)));
    exit->setBrush(QBrush(QColor(255, 107, 107)));

    this->connect(play, SIGNAL(clicked()), this, SLOT(playClicked()));
    this->connect(exit, SIGNAL(clicked()), this, SLOT(exitClicked()));

    QFont font;

    font = playText.font();
    font.setPixelSize(60);
    playText.setFont(font);
    exitText.setFont(font);

    playText.setPlainText("PLAY");
    exitText.setPlainText("EXIT");

    playText.setPos((this->width()/2 - playText.boundingRect().width()/2), 260.0f);
    exitText.setPos((this->width()/2 - exitText.boundingRect().width()/2), 410.0f);

    this->addItem(play);
    this->addItem(&playText);
    this->addItem(exit);
    this->addItem(&exitText);
}

void Menu::playClicked() {
    w->selection->init();
    w->setScene(w->selection);
}

void Menu::exitClicked() {
    w->close();
}
