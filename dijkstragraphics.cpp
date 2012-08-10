#include "dijkstragraphics.h"

DijkstraGraphics::DijkstraGraphics() : DijkstraAlgorithm()
{
}

void DijkstraGraphics::addToScene(QGraphicsScene *scene)
{
    foreach(DijkstraGraphicsNode *node, this->Nodes) {
        scene->addItem(node);
    }
    foreach(DijkstraGraphicsEdge *edge, this->Edges) {
        scene->addItem(edge);
    }
}
