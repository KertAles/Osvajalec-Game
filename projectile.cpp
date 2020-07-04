#include "projectile.h"
#include "mainwindow.h"

#include <QPropertyAnimation>
#include <QTime>
#include <QCoreApplication>
#include <cmath>

extern MainWindow* w;

Projectile::Projectile() {
}

void Projectile::launchArrow(Unit* source, Unit* dest) {
    this->setPixmap(QPixmap(":/images/Units/arrow.png"));
    w->bah->addItem(this);

    this->launch(source->pos(), dest->pos());

    delete this;
}

void Projectile::launchArrow(Unit* source, Building* dest) {
    this->setPixmap(QPixmap(":/images/Units/arrowBurning.png"));
    w->bah->addItem(this);

    this->launch(source->pos(), dest->pos());

    delete this;
}

void Projectile::launchArrow(Building* source, Unit* dest) {
    this->setPixmap(QPixmap(":/images/Units/arrow.png"));
    w->bah->addItem(this);

    this->launch(source->pos(), dest->pos());

    delete this;
}

void Projectile::launchBoulder(Building* source, Unit* dest) {
    this->setPixmap(QPixmap(":/images/Units/boulder.png"));
    w->bah->addItem(this);

    this->launch(source->pos(), dest->pos());

    delete this;
}

void Projectile::launch(QPointF source, QPointF dest) {

    double dx = (dest.x() - source.x());
    double dy = (dest.y() - source.y());

    this->setRotation(atan(dy / dx)*180 / 3.14);

    QPropertyAnimation* anime = new QPropertyAnimation(this,"pos");
    anime->setStartValue(source);
    dest.setX(dest.x()+UNITSIZE/2);
    dest.setY(dest.y()+UNITSIZE/2-7.0f);
    anime->setEndValue(dest);
    anime->setDuration(300);
    anime->start();
    anime->connect(anime, SIGNAL(finished()), anime, SLOT(deleteLater()));

    QTime dieTime = QTime::currentTime().addMSecs(300); //waits for animation to end
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

