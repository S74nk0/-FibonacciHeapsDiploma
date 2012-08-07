#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

#include "fibheapgraphics.h"

//! [0]
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void scaleView(qreal scaleFactor);

private:
    void addNode(GraphicsFibNode *node);
//    GraphicsNode<GraphicsEdge<GraphicsNode> > *centerGraphicsNode;
//    GraphicsNodeW *centerGraphicsNode;
    QList<GraphicsFibNode *> minExtr;
    FibHeapGraphics fibheap;
};

#endif // GRAPHWIDGET_H
