#include "fibheapwidget.h"

#include <QtGui>
#include <QFileDialog> // qt 5
#include <limits>
#include <QMessageBox>

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
    case Qt::Key_D:
        deSelect();
        break;
    case Qt::Key_M:
        GraphicsFibNode::colorMins = !GraphicsFibNode::colorMins;
        updateMin();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void FibHeapWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, +event->delta() / 240.0));
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

// FibHeap

void FibHeapWidget::extractMin()
{
    delete selectedHeap->ExtractMin();
    if(isFirst)
        GraphicsFibNode::minfNode = selectedHeap->Min();
    else
        GraphicsFibNode::minfNode2 = selectedHeap->Min();

    this->updateMin();
}

void FibHeapWidget::decreaseKey(int key)
{
    if(!GraphicsFibNode::selected) {
        QMessageBox::information( this, "Select a node", "In order to run this operation\n"
                                  "you must select a node first", QMessageBox::Ok, 0 );
        return;
    }

    GraphicsFibNode *Selected = GraphicsFibNode::selected;
    GraphicsFibNode::selected = 0;
    selectedHeap->DecreaseKey(Selected, key);
    this->updateMin();
}

void FibHeapWidget::deleteNode()
{
    if(!GraphicsFibNode::selected) {
        QMessageBox::information( this, "Select a node", "In order to run this operation\n"
                                  "you must select a node first", QMessageBox::Ok, 0 );
        return;
    }

    this->decreaseKey(std::numeric_limits<int>::min());

    isDelete = true;
}

void FibHeapWidget::updateMin()
{
    GraphicsFibNode *oldMin = 0;
    GraphicsFibNode *newMin = 0;
    if(isFirst)
    {
        oldMin = GraphicsFibNode::minfNode;
        GraphicsFibNode::minfNode = selectedHeap->Min();
        newMin = GraphicsFibNode::minfNode;
    }
    else
    {
        oldMin = GraphicsFibNode::minfNode2;
        GraphicsFibNode::minfNode2 = selectedHeap->Min();
        newMin = GraphicsFibNode::minfNode2;
    }

    if(newMin)
        newMin->update();
    if(oldMin && oldMin != newMin)
        oldMin->update();
}

bool FibHeapWidget::blockComponents()
{
    return selectedHeap->blockComponents();
}

void FibHeapWidget::nextStep()
{
    if(isDelete && selectedHeap->oneStatesLeft() && !selectedHeap->decreaseKeyTmpNode())
    {
        selectedHeap->clearPositions();
        this->extractMin();
        isDelete = false;
    }
    else if(selectedHeap->decreaseKeyTmpNode())
    {
        selectedHeap->clearPositions();
        selectedHeap->DecreaseKey(selectedHeap->Min(), std::numeric_limits<int>::max()); // dummy parameters
    }
    else
        this->selectedHeap->animate(420);
}

void FibHeapWidget::insertNode(int key)
{
    selectedHeap->Insert(key,this->scene());
    updateMin();
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

void FibHeapWidget::unionOperation()
{
    if(!firstFibHeap || !secondFibHeap )
        return;
    if(!firstFibHeap->Min() || !secondFibHeap->Min())
        return;

    GraphicsFibNode *Min1 = GraphicsFibNode::minfNode;
    GraphicsFibNode *Min2 = GraphicsFibNode::minfNode2;
    if(isFirst)
    {
        selectedHeap = selectedHeap->Union(secondFibHeap);
        GraphicsFibNode::minfNode = selectedHeap->Min();
        GraphicsFibNode::minfNode2 = 0;
        delete firstFibHeap;
        firstFibHeap = selectedHeap;
        delete secondFibHeap;
        secondFibHeap = new FibHeapGraphics();
    }
    else
    {
        selectedHeap = selectedHeap->Union(firstFibHeap);
        GraphicsFibNode::minfNode = 0;
        GraphicsFibNode::minfNode2 = selectedHeap->Min();
        delete firstFibHeap;
        firstFibHeap = new FibHeapGraphics();
        delete secondFibHeap;
        secondFibHeap = selectedHeap;
    }
    secondFibHeap->referencePoint = secondRefPoint;
    firstFibHeap->referencePoint = firstRefPoint;

    Min1->update();
    Min2->update();
    scene()->addItem(selectedHeap->edges().last());
    selectedHeap->animate(300);
}

void FibHeapWidget::ImportHeap()
{
    bool clear = false;
    if(selectedHeap->Min()) {
        if(QMessageBox::No ==
                QMessageBox::question(this,"Heap is not empty","Currently selected heap is not empty.\n" "Clear selected heap and import new?")) {
            return;
        } else {
            clear = true;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(), tr("FHeap (*.fibh)"));

    if(fileName != "") {
        if(clear) {
            clearSelected();
        }
        selectedHeap->ImportHeap(fileName, this->scene());
    }

    updateMin();
}


void FibHeapWidget::deSelect()
{
    GraphicsFibNode *old = GraphicsFibNode::selected;
    GraphicsFibNode::selected = 0;
    if(old)
        old->update();
}
