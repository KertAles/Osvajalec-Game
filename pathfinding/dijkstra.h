#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "gridsquare.h"

#include <QList>

class Dijkstra
{
public:
    Dijkstra();

    static QList<GridSquare*> findPath();
   /* std::vector<Node*> open;
    std::list<Node*> closed;
    std::list<Node*> path;

    void clearList(std::list<Node*> &list);
    void clearVector(std::vector<Node*> &vector);
    Node* getLowestG();
    void removeFromVector(Node* n, std::vector<Node*> &vector);
    void getNeighbours(Node* node, std::vector<Node*> &neighbours);
    bool isInClosed(Node* node);
    bool isInOpen(Node* node);
    void removeFromOpen(Node* n);
    void retracePath(Node *start, Node *finish);
    void drawPath();
    void clearPath();
    Node* getFromOpen(int x, int y);*/
};

#endif // DIJKSTRA_H
