#ifndef DIJKSTRAWIDGET_H
#define DIJKSTRAWIDGET_H

#include <QtGui/QGraphicsView>

#include "dijkstragraphics.h"

class DijkstraWidget : public QGraphicsView
{
    Q_OBJECT

public:
    DijkstraWidget(QWidget *parent = 0);

private:
    DijkstraGraphics dijkstraGraph;
};

#endif // DIJKSTRAWIDGET_H
