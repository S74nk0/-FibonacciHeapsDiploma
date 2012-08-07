#ifndef GRAPHICSFIBNODE_H
#define GRAPHICSFIBNODE_H

#include "graphicsedgetemplate.h"
#include "graphicsnodetemplate.h"
#include "fibnodebase.h"

class GraphicsFibNode : public GraphicsNode<GraphicsEdge<GraphicsFibNode> >,
        public FibNodeBase
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

    inline GraphicsFibNode * child() const { return static_cast<GraphicsFibNode *>(this->Child); }
    inline GraphicsFibNode * parent() const { return static_cast<GraphicsFibNode *>(this->Parent); }
    inline GraphicsFibNode * next() const {

        return static_cast<GraphicsFibNode *>(this->Next);
    }
    inline GraphicsFibNode * prev() const { return static_cast<GraphicsFibNode *>(this->Prev); }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void formTree(GraphicsFibNode *node);
    int getOffset(GraphicsFibNode *node);
};

#endif // GRAPHICSFIBNODE_H
