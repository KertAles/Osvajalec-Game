#include "mainwindow.h"
#include "uimanager.h"
#include "uicomponent.h"

extern MainWindow* w;

UIManager::UIManager() {
    this->setPos(0.0f, 0.0f);
    this->setHandlesChildEvents(false);
}

void UIManager::update() {
    QPointF zero(w->mapToScene(0.0f, 0.0f));
    this->setPos(zero);

    for(UIComponent* component : components) { //forić
        component->update();
    }
}

void UIManager::addComponent(UIComponent *newComponent) {
    this->addToGroup(newComponent);
    components.push_back(newComponent);
}
