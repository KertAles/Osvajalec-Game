#include "mainwindow.h"
#include "selectionscreen.h"
#include "player.h"

extern MainWindow* w;

SelectionScreen::SelectionScreen() {
    startGame = new MainMenuButton();
}

void SelectionScreen::init() {
    float colourRectSize = 30.0f;

    p1Colour.setRect(0.0f, 0.0f, colourRectSize, colourRectSize);
    p2Colour.setRect(0.0f, 0.0f, colourRectSize, colourRectSize);
    p3Colour.setRect(0.0f, 0.0f, colourRectSize, colourRectSize);
    p4Colour.setRect(0.0f, 0.0f, colourRectSize, colourRectSize);

    p1Colour.setPos(20.0f, 20.0f);
    p2Colour.setPos(20.0f, 70.0f);
    p3Colour.setPos(20.0f, 120.0f);
    p4Colour.setPos(20.0f, 170.0f);

    p1Colour.setBrush(QBrush(QColor(66, 137, 244)));
    p2Colour.setBrush(QBrush(QColor(249, 103, 67)));
    p3Colour.setBrush(QBrush(QColor(136, 234, 70)));
    p4Colour.setBrush(QBrush(QColor(182, 32, 216)));

    p1Name.setGeometry(70.0f, 20.0f, 300.0f, 30.0f);
    p2Name.setGeometry(70.0f, 70.0f, 300.0f, 30.0f);
    p3Name.setGeometry(70.0f, 120.0f, 300.0f, 30.0f);
    p4Name.setGeometry(70.0f, 170.0f, 300.0f, 30.0f);

    startGame->setRect(0.0f, 0.0f, 300.0f, 30.0f);
    startGame->setPos(70.0f, 220.0f);
    startGame->setBrush(QBrush(QColor(150, 255, 145)));
    this->connect(startGame, SIGNAL(clicked()), this, SLOT(startClicked()));

    QFont font;
    font = startText.font();
    font.setPixelSize(18);
    font.setBold(true);
    startText.setFont(font);

    startText.setPlainText("Start game");
    startText.setPos(70.0f + startGame->rect().width()/2 - startText.boundingRect().width()/2,
                     220.0f + startGame->rect().height()/2 - startText.boundingRect().height()/2);

    sizeCombo.setGeometry(390.0f, 220.0f, 80.0f, 30.0f);
    modeCombo.setGeometry(490.0f, 220.0f, 80.0f, 30.0f);

    sizeCombo.addItem("25x20");
    sizeCombo.addItem("30x25");
    sizeCombo.addItem("35x30");

    modeCombo.addItem("Normal");
    modeCombo.addItem("Testing");

    font.setPixelSize(14);
    errorMessage.setFont(font);
    errorMessage.setPos(70.0f, 270.0f);
    errorMessage.setDefaultTextColor(Qt::red);

    this->addItem(&p1Colour);
    this->addItem(&p2Colour);
    this->addItem(&p3Colour);
    this->addItem(&p4Colour);

    this->addWidget(&p1Name);
    this->addWidget(&p2Name);
    this->addWidget(&p3Name);
    this->addWidget(&p4Name);

    this->addWidget(&sizeCombo);
    this->addWidget(&modeCombo);

    this->addItem(startGame);
    this->addItem(&startText);
    this->addItem(&errorMessage);
}

void SelectionScreen::startClicked() {
    int sizeX = -1;
    int sizeY = -1;
    char mode = 'e';
    QList<Player*> players;
    bool validName = true;
    bool errorName = false;

    errorMessage.setPlainText("");

    if(p1Name.text().size() != 0) {
        validName = true;

        if(p1Name.text() == p2Name.text()) {
            validName = false;
        }
        if(p1Name.text() == p3Name.text()) {
            validName = false;
        }
        if(p1Name.text() == p4Name.text()) {
            validName = false;
        }

        if(validName) {
            players.push_back(new Player(p1Name.text(), p1Colour.brush().color()));
        }
        else errorName = true;
    }

    if(p2Name.text().size() != 0) {
        validName = true;

        if(p2Name.text() == p3Name.text()) {
            validName = false;
        }
        if(p2Name.text() == p4Name.text()) {
            validName = false;
        }

        if(validName) {
            players.push_back(new Player(p2Name.text(), p2Colour.brush().color()));
        }
        else errorName = true;
    }

    if(p3Name.text().size() != 0) {
        validName = true;

        if(p3Name.text() == p4Name.text()) {
            validName = false;
        }

        if(validName) {
            players.push_back(new Player(p3Name.text(), p3Colour.brush().color()));
        }
        else errorName = true;
    }

    if(p4Name.text().size() != 0) {
        players.push_back(new Player(p4Name.text(), p4Colour.brush().color()));
    }

    if(modeCombo.currentText() == "Normal") {
        mode = 'n';
    }
    else if(modeCombo.currentText() == "Testing") {
        mode = 't';
    }

    if(sizeCombo.currentText() == "25x20") {
        sizeX = 25;
        sizeY = 20;
    }
    else if(sizeCombo.currentText() == "30x25") {
        sizeX = 30;
        sizeY = 25;
    }
    else if(sizeCombo.currentText() == "35x30") {
        sizeX = 35;
        sizeY = 30;
    }

    if(players.size() == 0) {
        errorMessage.setPlainText("Ni imen! ");
    }
    if(players.size() == 1) {
        errorMessage.setPlainText("Samo en igralec! ");
    }
    if(errorName) {
        errorMessage.setPlainText(errorMessage.toPlainText() + "Napaka z imeni. ");
    }
    if(mode == 'e') {
        errorMessage.setPlainText(errorMessage.toPlainText() + "Napaka z mode. ");
    }
    if(sizeX == -1 || sizeY == -1) {
        errorMessage.setPlainText(errorMessage.toPlainText() + "Napaka z size. ");
    }

    if(errorMessage.toPlainText().size() == 0) {
        w->bah->init(players, sizeX, sizeY, mode);
        w->setScene(w->bah);
    }
}
