#ifndef DIJKSTRAWIDGET_H
#define DIJKSTRAWIDGET_H

//#include <QtGui/QGraphicsView>
#include <QGraphicsView> // qt 5
#include "dijkstragraphics.h"

class DijkstraWidget : public QGraphicsView
{
    Q_OBJECT

public:
    DijkstraWidget(QWidget *parent = 0);

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void scaleView(qreal scaleFactor);


private:
    DijkstraGraphics dijkstraGraph;
};

#endif // DIJKSTRAWIDGET_H
