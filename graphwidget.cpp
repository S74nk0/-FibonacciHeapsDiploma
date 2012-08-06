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
//! [0]

//! [1]
//    GraphicsNodeW *GraphicsNode1 = new GraphicsNodeW();
//    GraphicsNodeW *GraphicsNode2 = new GraphicsNodeW();
//    GraphicsNodeW *GraphicsNode3 = new GraphicsNodeW();
//    GraphicsNodeW *GraphicsNode4 = new GraphicsNodeW();
//    centerGraphicsNode = new GraphicsNodeW();
//    GraphicsNodeW *GraphicsNode6 = new GraphicsNodeW();
//    GraphicsNodeW *GraphicsNode7 = new GraphicsNodeW();
//    GraphicsNodeW *GraphicsNode8 = new GraphicsNodeW();
//    GraphicsNodeW *GraphicsNode9 = new GraphicsNodeW();
//    scene->addItem(GraphicsNode1);
//    scene->addItem(GraphicsNode2);
//    scene->addItem(GraphicsNode3);
//    scene->addItem(GraphicsNode4);
//    scene->addItem(centerGraphicsNode);
//    scene->addItem(GraphicsNode6);
//    scene->addItem(GraphicsNode7);
//    scene->addItem(GraphicsNode8);
//    scene->addItem(GraphicsNode9);
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode1, GraphicsNode2));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode2, GraphicsNode3));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode2, centerGraphicsNode));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode3, GraphicsNode6));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode4, GraphicsNode1));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode4, centerGraphicsNode));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(centerGraphicsNode, GraphicsNode6));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(centerGraphicsNode, GraphicsNode8));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode6, GraphicsNode9));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode7, GraphicsNode4));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode8, GraphicsNode7));
//    scene->addItem(new GraphicsEdge<GraphicsNodeW>(GraphicsNode9, GraphicsNode8));

//    GraphicsNode1->setPos(-50, -50);
//    GraphicsNode2->setPos(0, -50);
//    GraphicsNode3->setPos(50, -50);
//    GraphicsNode4->setPos(-50, 0);
//    centerGraphicsNode->setPos(0, 0);
//    GraphicsNode6->setPos(50, 0);
//    GraphicsNode7->setPos(-50, 50);
//    GraphicsNode8->setPos(0, 50);
//    GraphicsNode9->setPos(50, 50);

    for (int i = 1; i < 7/*21*/; ++i)
    {
        addNode(fibheap.Insert(i));
    }
    delete fibheap.ExtractMin(0);
//    fibheap.unlinkEdges();
//    fibheap.linkEdges();
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
        fibheap.unlinkEdges();
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

