#ifndef DIJKSTRAGRAPHICSEDGE_H
#define DIJKSTRAGRAPHICSEDGE_H

#include "dijkstragraphicsnode.h"

class DijkstraGraphicsEdge : public GraphicsEdge<DijkstraGraphicsNode>
{
public:
    DijkstraGraphicsEdge(DijkstraGraphicsNode *start, DijkstraGraphicsNode *end, int Price);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DIJKSTRAGRAPHICSEDGE_H
