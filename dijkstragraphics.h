#ifndef DIJKSTRAGRAPHICS_H
#define DIJKSTRAGRAPHICS_H

#include "dijkstraalgorithmtemplate.h"
#include "dijkstragraphicsnode.h"
#include "dijkstragraphicsedge.h"


class DijkstraGraphics
        : public DijkstraAlgorithm<DijkstraGraphicsNode, DijkstraGraphicsEdge>
{
public:
    DijkstraGraphics();

    void addToScene(QGraphicsScene *scene);

};

#endif // DIJKSTRAGRAPHICS_H
