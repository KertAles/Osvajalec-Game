#-------------------------------------------------
#
# Project created by QtCreator 2016-12-27T12:05:24
#
#-------------------------------------------------

QT       += core gui

CONFIG  += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperProjekt
TEMPLATE = app
MOC_DIR = release/build/moc
OBJECTS_DIR = release/build/obj
RCC_DIR = release/

SOURCES += main.cpp\
        mainwindow.cpp \
    gridsquare.cpp \
    game.cpp \
    resource.cpp \
    player.cpp \
    mapcheck.cpp \
    UI/uitopbar.cpp \
    UI/uimanager.cpp \
    UI/uibottombar.cpp \
    Units/worker.cpp \
    Units/knight.cpp \
    Units/archer.cpp \
    Units/pikeman.cpp \
    unit.cpp \
    uicomponent.cpp \
    Buildings/fort.cpp \
    Buildings/woodcamp.cpp \
    Buildings/mine.cpp \
    Buildings/farm.cpp \
    building.cpp \
    queueunit.cpp \
    queuebuilding.cpp \
    actionbutton.cpp \
    queueitem.cpp \
    stockpile.cpp \
    maprevealer.cpp \
    menu.cpp \
    Buildings/base.cpp \
    Buttons/mainmenubutton.cpp \
    upkeep.cpp \
    projectile.cpp \
    unitmover.cpp \
    victoryscreen.cpp \
    influence.cpp \
    influencecalculator.cpp \
    ai.cpp \
    aivision.cpp \
    resourcedemand.cpp \
    selectionscreen.cpp \
    pathfinding/dijkstra.cpp \
    pathfinding/bresenham.cpp \
    pathfinding/distance.cpp

HEADERS  += mainwindow.h \
    gridsquare.h \
    game.h \
    resource.h \
    player.h \
    mapcheck.h \
    UI/uibottombar.h \
    UI/uitopbar.h \
    UI/uimanager.h \
    Units/worker.h \
    Units/knight.h \
    Units/archer.h \
    Units/pikeman.h \
    uicomponent.h \
    unit.h \
    Buildings/fort.h \
    Buildings/woodcamp.h \
    Buildings/mine.h \
    Buildings/farm.h \
    building.h \
    queueunit.h \
    queuebuilding.h \
    actionbutton.h \
    queueitem.h \
    stockpile.h \
    maprevealer.h \
    menu.h \
    Buildings/base.h \
    Buttons/mainmenubutton.h \
    upkeep.h \
    projectile.h \
    unitmover.h \
    victoryscreen.h \
    influence.h \
    influencecalculator.h \
    ai.h \
    aivision.h \
    resourcedemand.h \
    selectionscreen.h \
    pathfinding/dijkstra.h \
    pathfinding/bresenham.h \
    pathfinding/distance.h

FORMS    +=

QMAKE_CXXFLAGS  += -std=c++0x

RESOURCES += \
    res.qrc
