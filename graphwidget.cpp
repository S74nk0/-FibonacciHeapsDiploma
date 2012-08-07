#include "graphwidget.h"

#include <QtGui>

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

    selectedHeap = &fibheap;

//    for (int i = 1; i < 7/*21*/; ++i)
//    {
//        addNode(fibheap.Insert(i));
//    }
//    fibheap.setStates();
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;

    case Qt::Key_M:
        this->extractMin();
        break;
        //debuging
    case Qt::Key_D:

        this->decreaseKey();

        break;
    case Qt::Key_A:

        this->selectedHeap->animate(420);

        break;

    case Qt::Key_I:

        addNode(selectedHeap->Insert(5));

        break;

        //debuging
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

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
        scene()->addItem(node->edges().first());
    }
    selectedHeap->animateInsert();
}

void GraphWidget::extractMin()
{
    delete selectedHeap->ExtractMin(0);
    GraphicsFibNode::minfNode = selectedHeap->Min();
    this->updateMin();
}

void GraphWidget::decreaseKey()
{
    if(!GraphicsFibNode::selected)
        return;

    selectedHeap->DecreaseKey(GraphicsFibNode::selected, -8);
    selectedHeap->updateEdges();
    this->updateMin();
}

void GraphWidget::updateMin()
{
    GraphicsFibNode *oldMin = GraphicsFibNode::minfNode;
    GraphicsFibNode::minfNode = fibheap.Min();
    if(GraphicsFibNode::minfNode)
        GraphicsFibNode::minfNode->update();
    if(oldMin && oldMin != GraphicsFibNode::minfNode)
        oldMin->update();
}
