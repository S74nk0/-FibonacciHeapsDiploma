#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

#include "fibheapgraphics.h"


class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    void extractMin();
    void decreaseKey();
    void deleteNode();

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void scaleView(qreal scaleFactor);

private:
    void addNode(GraphicsFibNode *node);
    void updateMin();

    FibHeapGraphics *selectedHeap;
    FibHeapGraphics fibheap;
};

#endif // GRAPHWIDGET_H
