#include <QPainter>
#include "graphicsedge.h"


template <class GNode>
GraphicsEdge<GNode>::GraphicsEdge(GNode *startNode, GNode *endNode)
    : Edge<GNode>(startNode,endNode), arrowSize(10) // nism sigurn ce je arrow size potreben? !!!! zgleda da ni
{
    setAcceptedMouseButtons(0);
    setZValue(-2);
    this->startN->addEdge(this);
    this->endN->addEdge(this);
    adjust();
}

template <class GNode>
GraphicsEdge<GNode>::GraphicsEdge(GNode *startNode, GNode *endNode, int Price)
    : Edge<GNode>(startNode,endNode, Price), arrowSize(20)
{
    setAcceptedMouseButtons(0);
    setZValue(-2);
    this->startN->addEdge(this);
    this->endN->addEdge(this);
    adjust();
}

template <class GNode>
void GraphicsEdge<GNode>::adjust()
{
    if (!this->startN || !this->endN)
        return;

    QLineF line(mapFromItem(this->startN, 0, 0), mapFromItem(this->endN, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        startPoint = line.p1() + edgeOffset;
        endPoint = line.p2() - edgeOffset;
    } else {
        startPoint = endPoint = line.p1();
    }
}

template <class GNode>
QRectF GraphicsEdge<GNode>::boundingRect() const
{
    if (!this->startN || !this->endN)
        return QRectF();

    return QRectF(startPoint, QSizeF(endPoint.x() - startPoint.x(),
                                      endPoint.y() - startPoint.y()));
}

template <class GNode>
void GraphicsEdge<GNode>::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!this->startN || !this->endN)
        return;

    QLineF line(startPoint, endPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);
}

template <class GNode>
void GraphicsEdge<GNode>::setNodes(GNode *startNode, GNode *endNode)
{
    this->startN = startNode;
    this->endN = endNode;
    this->startN->addEdge(this);
    this->endN->addEdge(this);
    adjust();
}

template <class GNode>
bool GraphicsEdge<GNode>::unlink()
{
    if (!this->startN || !this->endN)
        return false;

    bool returnSuccess = this->startN->removeEdge(this) && this->endN->removeEdge(this);

    this->startN = this->endN = 0;

    return returnSuccess;
}

