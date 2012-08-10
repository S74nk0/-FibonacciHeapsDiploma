#ifndef DIJKSTRAGRAPHICSEDGE_H
#define DIJKSTRAGRAPHICSEDGE_H

#include "dijkstragraphicsnode.h"

class DijkstraGraphicsEdge : public GraphicsEdge<DijkstraGraphicsNode>
{
public:
    DijkstraGraphicsEdge(DijkstraGraphicsNode *start, DijkstraGraphicsNode *end, int Price);

};

#endif // DIJKSTRAGRAPHICSEDGE_H
