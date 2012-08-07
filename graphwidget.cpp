#include "graphwidget.h"

#include <QtGui>

//#include <math.h>

//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-20000, -20000, 40000, 40000);

    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(400, 400);
    setWindowTitle(tr("Fibonacci Heaps"));

    setDragMode(QGraphicsView::ScrollHandDrag);

    for (int i = 1; i < 21; ++i)
    {
        addNode(fibheap.Insert(i));
    }
    delete fibheap.ExtractMin(0);
}
//! [1]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
        //debuging
    case Qt::Key_D:
        delete fibheap.ExtractMin(0);
        break;
        //debuging
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]


//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

//NEW SHIT
//******************///////////

void GraphWidget::addNode(GraphicsFibNode *node)
{
    scene()->addItem(node);

    if(node->edges().count() == 1)
    {
        scene()->addItem(node->edges()[0]);
    }
}

