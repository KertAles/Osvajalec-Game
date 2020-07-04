#include "uitopbar.h"

#include <QBrush>
#include <QFont>

extern MainWindow* w;

UITopBar::UITopBar() {
    menuB = new ActionButton(100, 30);
}

UITopBar::~UITopBar() {
    if(menuB)
        delete menuB;
}

void UITopBar::init(float width, float height) {
    bar.setRect(0.0f, 0.0f, width, height);
    this->addToGroup(&bar);
    bar.setPos(0.0f, 0.0f);

    bar.setBrush(QBrush(Qt::white));

    this -> setHandlesChildEvents(false);

    menuB->setPos(w->width()-80.0f, 5.0f);

    float blockWidth = 180.0f;
    float n = 20.0f;
    float topMargin = 3.0f;
    float iconSize = 40.0f;

    foodIcon.setPos(n, topMargin);
    woodIcon.setPos(n + blockWidth, topMargin);
    ironIcon.setPos(n + blockWidth*2, topMargin);
    goldIcon.setPos(n + blockWidth*3, topMargin);

    foodData.setPos(n + iconSize, topMargin);
    woodData.setPos(n + blockWidth + iconSize, topMargin);
    ironData.setPos(n + blockWidth*2 + iconSize, topMargin);
    goldData.setPos(n + blockWidth*3 + iconSize, topMargin);


    foodIcon.setPixmap(QPixmap(":/images/UI/foodIcon.png"));
    woodIcon.setPixmap(QPixmap(":/images/UI/woodIcon.png"));
    ironIcon.setPixmap(QPixmap(":/images/UI/ironIcon.png"));
    goldIcon.setPixmap(QPixmap(":/images/UI/goldIcon.png"));

    QFont font;

    font = foodData.font();
    font.setPixelSize(32);
    foodData.setFont(font);
    woodData.setFont(font);
    ironData.setFont(font);
    goldData.setFont(font);

    this->addToGroup(menuB);

    this->addToGroup(&foodIcon);
    this->addToGroup(&woodIcon);
    this->addToGroup(&ironIcon);
    this->addToGroup(&goldIcon);

    this->addToGroup(&foodData);
    this->addToGroup(&woodData);
    this->addToGroup(&ironData);
    this->addToGroup(&goldData);
}

void UITopBar::update() {

}

void UITopBar::updateResData(Player *player) {
    QString data;
    Stockpile stock = player->getStockpile();

    data = QString::number(stock.getFood());
    data += "(";
    if(player->getFoodInc()>=0)
        data += "+";
    data += QString::number(player->getFoodInc());
    data += ")";
    foodData.setPlainText(data);

    data = QString::number(stock.getWood());
    data += "(";
    if(player->getWoodInc()>=0)
        data += "+";
    data += QString::number(player->getWoodInc());
    data += ")";
    woodData.setPlainText(data);

    data = QString::number(stock.getIron());
    data += "(";
    if(player->getIronInc()>=0)
        data += "+";
    data += QString::number(player->getIronInc());
    data += ")";
    ironData.setPlainText(data);

    data = QString::number(stock.getGold());
    data += "(";
    if(player->getGoldInc()>=0)
        data += "+";
    data += QString::number(player->getGoldInc());
    data += ")";
    goldData.setPlainText(data);
}
