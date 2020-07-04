#include "unitmover.h"
#include "projectile.h"
#include "mainwindow.h"

#include <QPropertyAnimation>
#include <QTime>
#include <QCoreApplication>

extern MainWindow* w;

UnitMover::UnitMover()
{

}


void UnitMover::moveSmooth(Unit* unit, GridSquare* newPos) {
    QPropertyAnimation* anime = new QPropertyAnimation(unit,"pos");
    QPointF endPoint = unit->pos();
    endPoint.setX(newPos->getX()+SQUARESIZE -(UNITSIZE + 7));
    endPoint.setY(newPos->getY() + 6);
    anime->setStartValue(unit->pos());
    anime->setEndValue(endPoint);
    anime->setDuration(300);
    anime->start();
    anime->connect(anime, SIGNAL(finished()), anime, SLOT(deleteLater()));

    QTime dieTime = QTime::currentTime().addMSecs(300); //waits for animation to end
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void UnitMover::attack(Unit* attacker, Unit* defender) {
    if(attacker->getType() == 'a') {
        Projectile* arrow = new Projectile;
        arrow->launchArrow(attacker, defender);
    }
    else {
    QPropertyAnimation* anime = new QPropertyAnimation(attacker,"pos");
    QPointF startPoint = attacker->pos();
    anime->setStartValue(startPoint);
    anime->setEndValue(defender->pos());
    anime->setDuration(150);
    anime->start();
    anime->connect(anime, SIGNAL(finished()), anime, SLOT(deleteLater()));

    QTime dieTime = QTime::currentTime().addMSecs(75); //waits for animation to end
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    anime = new QPropertyAnimation(attacker,"pos");
    anime->setStartValue(attacker->pos());
    anime->setEndValue(startPoint);
    anime->setDuration(150);
    anime->start();
    anime->connect(anime, SIGNAL(finished()), anime, SLOT(deleteLater()));

    dieTime= QTime::currentTime().addMSecs(75); //waits for animation to end
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void UnitMover::attack(Unit* attacker, Building* defender) {
    if(attacker->getType() == 'a') {
        Projectile* arrow = new Projectile;
        arrow->launchArrow(attacker, defender);
    }
    else {
    QPropertyAnimation* anime = new QPropertyAnimation(attacker,"pos");
    QPointF startPoint = attacker->pos();
    anime->setStartValue(startPoint);
    anime->setEndValue(defender->pos());
    anime->setDuration(150);
    anime->start();
    anime->connect(anime, SIGNAL(finished()), anime, SLOT(deleteLater()));

    QTime dieTime = QTime::currentTime().addMSecs(75); //waits for animation to end
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    anime = new QPropertyAnimation(attacker,"pos");
    anime->setStartValue(attacker->pos());
    anime->setEndValue(startPoint);
    anime->setDuration(150);
    anime->start();
    anime->connect(anime, SIGNAL(finished()), anime, SLOT(deleteLater()));

    dieTime= QTime::currentTime().addMSecs(75); //waits for animation to end
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void UnitMover::biteBack(Unit* defender, Unit* attacker) {
    Projectile* arrow = new Projectile;
    arrow->launchArrow(defender, attacker);
}

void UnitMover::biteBack(Building *defender, Unit *attacker) {
    Projectile* projectile = new Projectile;
    if(defender->getDefense() != 0 && defender->getDefense() <= 50) //if under 50 launch arrow
        projectile->launchArrow(defender, attacker);
    else if(defender->getDefense() > 50) //if above 50 launch boulder
        projectile->launchBoulder(defender,attacker);
}
