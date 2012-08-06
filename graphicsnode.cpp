#include "graphicsnode.h"


#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>


template <class GEdgeTemplate>
GraphicsNode<GEdgeTemplate>::GraphicsNode()
{
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

template <class GEdgeTemplate>
void GraphicsNode<GEdgeTemplate>::addEdge(GEdgeTemplate *edge)
{
    edgeList << edge;
    edge->adjust();
}
template <class GEdgeTemplate>
QList<GEdgeTemplate *> GraphicsNode<GEdgeTemplate>::edges() const
{
    return edgeList;
}


template <class GEdgeTemplate>
QRectF GraphicsNode<GEdgeTemplate>::boundingRect() const
{
//    qreal adjust = 2;
//    return QRectF( -10 - adjust, -10 - adjust,
//                  23 + adjust, 23 + adjust);
    qreal adjust = 20;
    return QRectF(-10 - adjust, -10 - adjust,
                  /*23 + adjust*/100, 23 + adjust);
}


template <class GEdgeTemplate>
QPainterPath GraphicsNode<GEdgeTemplate>::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}


template <class GEdgeTemplate>
void GraphicsNode<GEdgeTemplate>::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {
        gradient.setColorAt(0, Qt::blue);
    }
    else {
        gradient.setColorAt(0, Qt::yellow);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}


template <class GEdgeTemplate>
QVariant GraphicsNode<GEdgeTemplate>::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (GEdgeTemplate *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

template <class GEdgeTemplate>
void GraphicsNode<GEdgeTemplate>::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

template <class GEdgeTemplate>
void GraphicsNode<GEdgeTemplate>::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}


template <class GEdgeTemplate>
bool GraphicsNode<GEdgeTemplate>::removeEdge(GEdgeTemplate *edge)
{
    return edgeList.removeOne(edge);
}

