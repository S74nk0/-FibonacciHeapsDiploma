#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>

#include "fibheapgraphics.h"


class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = 0);

    bool blockComponents();
    void nextStep();
    void insertNode(int key);
    void ExportHeap();

    void extractMin();
    void decreaseKey(int key);
    void deleteNode();
    void clearSelected();

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

    GraphicsFibNode **selectedMin;
    FibHeapGraphics *selectedHeap;
    FibHeapGraphics *firstFibHeap;
    FibHeapGraphics *secondFibHeap;
    bool isDelete;
    bool first;
};

#endif // GRAPHWIDGET_H
