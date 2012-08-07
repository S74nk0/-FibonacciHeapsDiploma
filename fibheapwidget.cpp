#include "fibheapwidget.h"

#include <QtGui>
#include <limits>

FibHeapWidget::FibHeapWidget(QWidget *parent)
    : QGraphicsView(parent), isDelete(false), isFirst(true)
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
    setMinimumSize(500, 500);
    setWindowTitle(tr("Fibonacci Heaps"));

    setDragMode(QGraphicsView::ScrollHandDrag);


    firstFibHeap = new FibHeapGraphics();
    secondFibHeap = new FibHeapGraphics();

    firstRefPoint = QPointF();
    secondRefPoint = QPointF(-100.0, 400.0);

    firstFibHeap->referencePoint = firstRefPoint;
    secondFibHeap->referencePoint = secondRefPoint;

    //the ref points are for node positioning

    selectedHeap = firstFibHeap;


//    for (int i = 1; i < 7/*21*/; ++i)
//    {
//        addNode(fibheap.Insert(i));
//    }
//    fibheap.setStates();
}

void FibHeapWidget::keyPressEvent(QKeyEvent *event)
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

        this->decreaseKey(-20);

        break;
    case Qt::Key_A:

        this->selectedHeap->animate(420);

        break;

    case Qt::Key_I:

        addNode(selectedHeap->Insert(5));

        break;
    case Qt::Key_R:

        deleteNode();

        break;

        //debuging
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void FibHeapWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void FibHeapWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void FibHeapWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void FibHeapWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

//NEW SHIT
//******************///////////

void FibHeapWidget::addNode(GraphicsFibNode *node)
{
    scene()->addItem(node);

    if(node->edges().count() == 1)
    {
        scene()->addItem(node->edges().first());
    }
    updateMin();
    selectedHeap->animateInsert();
}

void FibHeapWidget::extractMin()
{
    delete selectedHeap->ExtractMin(0);
    GraphicsFibNode::minfNode = selectedHeap->Min();
    this->updateMin();
}

void FibHeapWidget::decreaseKey(int key)
{
    if(!GraphicsFibNode::selected)
        return;

    GraphicsFibNode *Selected = GraphicsFibNode::selected;
    GraphicsFibNode::selected = 0;
    selectedHeap->saveCurrentPositions();
    selectedHeap->DecreaseKey(Selected, key);
    selectedHeap->updateEdges();
    this->updateMin();
    selectedHeap->setFirstPositions(); // set first
    selectedHeap->animate(300);
}

void FibHeapWidget::deleteNode()
{
    if(!GraphicsFibNode::selected)
        return;

    this->decreaseKey(std::numeric_limits<int>::min());

    isDelete = true;
}

void FibHeapWidget::updateMin()
{
    GraphicsFibNode *oldMin = GraphicsFibNode::minfNode;
    GraphicsFibNode::minfNode = selectedHeap->Min();
    if(GraphicsFibNode::minfNode)
        GraphicsFibNode::minfNode->update();
    if(oldMin && oldMin != GraphicsFibNode::minfNode)
        oldMin->update();
}

bool FibHeapWidget::blockComponents()
{
    return selectedHeap->blockComponents();
}

void FibHeapWidget::nextStep()
{
    if(isDelete)
    {
        selectedHeap->clearPositions();
        isDelete = false;
        this->extractMin();
    }
    else
        this->selectedHeap->animate(420);
}

void FibHeapWidget::insertNode(int key)
{
    addNode(selectedHeap->Insert(key));
}

void FibHeapWidget::clearSelected()
{
    selectedHeap->clear();
    if(isFirst)
        GraphicsFibNode::minfNode = 0;
    else
        GraphicsFibNode::minfNode2 = 0;
}

void FibHeapWidget::ExportHeap()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "",
                                tr("Heaps (*.fibh)"));

    if(fileName != "")
        selectedHeap->ExportHeap(fileName);
}


void FibHeapWidget::switchHeap()
{
    isFirst = !isFirst;

    if(isFirst)
        selectedHeap = firstFibHeap;
    else
        selectedHeap = secondFibHeap;

}

void FibHeapWidget::reset()
{
    firstFibHeap->clear();
    secondFibHeap->clear();
    GraphicsFibNode::minfNode = 0;
    GraphicsFibNode::minfNode2 = 0;
}
