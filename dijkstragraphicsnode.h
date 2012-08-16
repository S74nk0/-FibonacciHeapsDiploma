#ifndef DIJKSTRAGRAPHICSNODE_H
#define DIJKSTRAGRAPHICSNODE_H

#include "graphicsedgetemplate.h"
#include "graphicsnodetemplate.h"
#include "fibnodebasetemplate.h"
#include "nodebase.h"

class DijkstraGraphicsNode
        : public GraphicsNode<GraphicsEdge<DijkstraGraphicsNode> >
        , public FibNodeBase<DijkstraGraphicsNode>
        , public NodeBase<Edge<DijkstraGraphicsNode> >
{
public:
    DijkstraGraphicsNode();
    DijkstraGraphicsNode(int id, int key);

    static DijkstraGraphicsNode *searchStartNode;
    static DijkstraGraphicsNode *searchEndNode;
    static int selectCount;

    static void resetCount() { selectCount = 0; }
    bool routeNode;

    //dummdy functions to satisfy the template (there is probably a better way but this is for now the easiest way and with no pefrormance penaulty (extremaley small if any, probabley none))
    inline void setStates() const {}
    inline void update() const {}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // DIJKSTRAGRAPHICSNODE_H
