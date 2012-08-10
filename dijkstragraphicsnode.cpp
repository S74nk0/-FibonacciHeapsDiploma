#include "dijkstragraphicsnode.h"

DijkstraGraphicsNode::DijkstraGraphicsNode()
    : GraphicsNode(), FibNodeBase(), NodeBase()
{
}

DijkstraGraphicsNode::DijkstraGraphicsNode(int id, int key)
    : GraphicsNode(), FibNodeBase(key), NodeBase(id)
{
}


void DijkstraGraphicsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicsNode::paint(painter, option, widget);
    QString num = QString::number(this->nodeId);
    painter->drawText(-5*num.size(),5, num);
}
