#include "dijkstrawidget.h"

#include <QtGui>

DijkstraWidget::DijkstraWidget(QWidget *parent)
    : QGraphicsView(parent)
{

    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-20000, -20000, 40000, 40000);

    QString name = "scotland_big.txt";
//    QString name = "primerGraf.txt";
//    QString name = "primerGraf2.txt";
    dijkstraGraph.loadGraph(name);
    dijkstraGraph.addToScene(scene);

    setScene(scene);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setRenderHint(QPainter::Antialiasing, false);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(500, 500);
    setWindowTitle(tr("Dijkstra "));

    setDragMode(QGraphicsView::ScrollHandDrag);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);


    dijkstraGraph.calculatePositions();
//    dijkstraGraph.calculateForces();
}


void DijkstraWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void DijkstraWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void DijkstraWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;

    case Qt::Key_D:
        dijkstraGraph.doAlg();
        dijkstraGraph.markRoute();
        dijkstraGraph.hideUnmarked();
        break;

    case Qt::Key_S:
        DijkstraGraphicsNode::resetCount();
        break;

    case Qt::Key_A:
        dijkstraGraph.calculatePositions();
        break;

    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void DijkstraWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, +event->delta() / 240.0));
}

void DijkstraWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
