#ifndef GRAPHICSFIBNODE_H
#define GRAPHICSFIBNODE_H

#include "graphicsedgetemplate.h"
#include "graphicsnodetemplate.h"
#include "fibnodebasetemplate.h"

class GraphicsFibNode : public GraphicsNode<GraphicsEdge<GraphicsFibNode> >,
        public FibNodeBase<GraphicsFibNode>
{
public:
    GraphicsFibNode();
    GraphicsFibNode(int k);
    GraphicsFibNode(int k, int d, bool m);
    ~GraphicsFibNode();

    void makeChildLink(GraphicsFibNode *child);

    //static members
    static GraphicsFibNode *minfNode;
    static GraphicsFibNode *minfNode2;
    static GraphicsFibNode *selected;

    //implement this function
    void setStates();
    void savePositions(GraphicsFibNode *node);
    QList<QPointF> positions;
    QPointF referencePoint; // this could be done in a better way, it's kinda stupid to do it like this but what the heck

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void formTree(GraphicsFibNode *node);
    int getOffset(GraphicsFibNode *node);
};

#endif // GRAPHICSFIBNODE_H
