#include "dijkstragraphicsedge.h"

#include "math.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

DijkstraGraphicsEdge::DijkstraGraphicsEdge(DijkstraGraphicsNode *start, DijkstraGraphicsNode *end, int Price)
    : GraphicsEdge(start, end)
{
    this->price = Price;
    startN->toEdges.push_back(this);
    endN->fromEdges.push_back(this);
}


void DijkstraGraphicsEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (!this->startN || !this->endN)
        return;

//    QLineF line(startPoint, endPoint); // original

    //testing

    QLineF line(startPoint, endPoint);
//    line.translate((startPoint+endPoint)/2);
    //testing

    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
//    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

//    Draw the price number
    QString num = QString::number(this->price);
    painter->drawText(((this->startPoint.x() + endPoint.x())/2), ((startPoint.y() + endPoint.y())/2), num);


    // Draw the arrows
    double angle = ::acos(line.dx() / line.length());
    if (line.dy() >= 0)
        angle = TwoPi /*M_PI*2.0*/ - angle;

    QPointF destArrowP1 = endPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = endPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
