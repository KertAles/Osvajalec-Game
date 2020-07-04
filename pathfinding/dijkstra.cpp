#include "pathfinding/dijkstra.h"

Dijkstra::Dijkstra()
{

}

QList<GridSquare*> Dijkstra::findPath()
{
   /* clearPath();
    clearVector(open);
    clearList(closed);
    clearList(path);

    Node *startNode = grid.getStart();
    startNode->G = 0;


    open.push_back(startNode);
    Node *finishNode = grid.getFinish();

    Node *currentNode;
    bool foundPath = false;

    while(open.size() > 0)
    {
        currentNode = getLowestG();
        removeFromVector(currentNode, open);
        closed.push_back(currentNode);

        if(currentNode->equals(finishNode))
        {
            foundPath = true;
            finishNode = currentNode;
            break;
        }

        std::vector<Node*> neighbours;
        for(int i=0; i<8; i++)
            neighbours.push_back(new Node);

        getNeighbours(currentNode, neighbours);
        for(Node* neighbour : neighbours)
        {
            if(neighbour == nullptr)
                continue;

            int newCost = currentNode->G + currentNode->distance(neighbour);

            if(newCost < neighbour->G)
            {
                neighbour->G = newCost;
                neighbour->parent = currentNode;
            }
        }
    }

    if(finishNode->parent != nullptr && foundPath)
    {
        retracePath(startNode, finishNode);
    }


    drawPath();

    delete startNode;
    delete finishNode;*/
}
