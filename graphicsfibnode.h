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

    //static members
    static GraphicsFibNode *minfNode;
    static GraphicsFibNode *minfNode2;
    static GraphicsFibNode *selected;

    //implement this function
    void setStates();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void formTree(GraphicsFibNode *node);
    int getOffset(GraphicsFibNode *node);
};

#endif // GRAPHICSFIBNODE_H
