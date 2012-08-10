#include "dijkstragraphicsedge.h"

DijkstraGraphicsEdge::DijkstraGraphicsEdge(DijkstraGraphicsNode *start, DijkstraGraphicsNode *end, int Price)
    : GraphicsEdge(start, end)
{
    this->price = Price;
    startN->toEdges.push_back(this);
    endN->fromEdges.push_back(this);
}
