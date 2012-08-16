#include "dijkstragraphicsnode.h"

DijkstraGraphicsNode *DijkstraGraphicsNode::searchStartNode = 0;
DijkstraGraphicsNode *DijkstraGraphicsNode::searchEndNode = 0;
int DijkstraGraphicsNode::selectCount = 0;

DijkstraGraphicsNode::DijkstraGraphicsNode()
    : GraphicsNode(), FibNodeBase(), NodeBase(), routeNode(false)
{
}

DijkstraGraphicsNode::DijkstraGraphicsNode(int id, int key)
    : GraphicsNode(), FibNodeBase(key), NodeBase(id), routeNode(false)
{
}


void DijkstraGraphicsNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QRadialGradient gradient(-3, -3, 10);
//    if (option->state & QStyle::State_Sunken) {
//        gradient.setColorAt(0, Qt::blue);
//    }
//    else {
//        if(this->routeNode)
//            gradient.setColorAt(0, Qt::darkYellow);
//        else
//            gradient.setColorAt(0, Qt::yellow);
//    }

//    if (this->searchEndNode == this) {
//        gradient.setColorAt(0, Qt::blue);
//    }
//    if (this->searchStartNode == this) {
//        gradient.setColorAt(0, Qt::green);
//    }

    painter->setBrush(QBrush(Qt::yellow));
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);


    QString num = QString::number(this->nodeId);
    painter->drawText(-5*num.size(),5, num);
}

void DijkstraGraphicsNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    DijkstraGraphicsNode *oldNode = 0;
    if(selectCount == 0)
    {
        oldNode = DijkstraGraphicsNode::searchStartNode;
        DijkstraGraphicsNode::searchStartNode = this;
    }
    if(selectCount == 1)
    {
        oldNode = DijkstraGraphicsNode::searchEndNode;
        DijkstraGraphicsNode::searchEndNode = this;
    }

    if(oldNode)
        oldNode->update();

    selectCount++;

    update();
    QGraphicsItem::mousePressEvent(event);
}
