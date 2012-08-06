#ifndef GRAPHICSEDGE_H
#define GRAPHICSEDGE_H


#include <QGraphicsItem>
#include "edge.h"

template <class GNode>
class GraphicsEdge : public QGraphicsItem, public Edge<GNode>
{
public:
    GraphicsEdge(GNode *startNode, GNode *endNode);

    enum { Type = UserType + 2 };
    int type() const { return Type; }

    void adjust();
    void setNodes(GNode *startNode, GNode *endNode);
    bool unlink();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QPointF startPoint;
    QPointF endPoint;
    qreal arrowSize; // ni potrebno
};

#endif // GRAPHICSEDGE_H
