#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H


#include <QGraphicsItem>
#include <QList>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

template <class GEdgeTemplate>
class GraphicsNode : public QGraphicsItem
{
public:
    GraphicsNode();

    void addEdge(GEdgeTemplate *edge);
    QList<GEdgeTemplate *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    bool removeEdge(GEdgeTemplate *edge);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

//private:
    QList<GEdgeTemplate *> edgeList;
    QPointF newPos;
};

#endif // GRAPHICSNODE_H
