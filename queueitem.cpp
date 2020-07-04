#include "mainwindow.h"
#include "queueitem.h"

extern MainWindow* w;

QueueItem::QueueItem(){
    owner = nullptr;
    pos = nullptr;
}

void QueueItem::countdown() {
    turnsLeft--;
    qDebug() << "Countdown for" << type << " Left: " << turnsLeft;
    if(turnsLeft < 1) {
        createItem();
    }
}
