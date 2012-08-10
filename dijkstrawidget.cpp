#include "dijkstrawidget.h"

DijkstraWidget::DijkstraWidget(QWidget *parent)
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
    setMinimumSize(500, 500);
    setWindowTitle(tr("Dijkstra "));

    setDragMode(QGraphicsView::ScrollHandDrag);


//    QString name = "scotland_big.txt";
    QString name = "primerGraf.txt";
    dijkstraGraph.loadGraph(name);
    dijkstraGraph.addToScene(this->scene());
}
