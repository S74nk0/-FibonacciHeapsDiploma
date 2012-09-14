#ifndef GRAPHICSFIBEDGE_H
#define GRAPHICSFIBEDGE_H

#include "graphicsfibnode.h"

class GraphicsFibEdge : public GraphicsEdge<GraphicsFibNode>
{
public:
    GraphicsFibEdge(GraphicsFibNode *start, GraphicsFibNode *end) :
        GraphicsEdge(start, end) {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        if (!this->startN || !this->endN)
            return;

        QLineF line(startPoint, endPoint);
        if (qFuzzyCompare(line.length(), qreal(0.)))
            return;

        // Draw the line itself
        if(this->startN->root && this->endN->root) {
            painter->setPen(QPen(Qt::black, 1, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
        }
        else {
            painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }
        painter->drawLine(line);
    }
};

#endif // GRAPHICSFIBEDGE_H
