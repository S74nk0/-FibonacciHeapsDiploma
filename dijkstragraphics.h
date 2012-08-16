#ifndef DIJKSTRAGRAPHICS_H
#define DIJKSTRAGRAPHICS_H

#include "dijkstraalgorithmtemplate.h"
#include "dijkstragraphicsnode.h"
#include "dijkstragraphicsedge.h"


class FibHeapDG : public FibHeapBase<DijkstraGraphicsNode>
{};


class DijkstraGraphics
        : public DijkstraAlgorithm<DijkstraGraphicsNode, DijkstraGraphicsEdge>
{
public:
    DijkstraGraphics();

    void calculatePositions();

    void addToScene(QGraphicsScene *scene);
    void doAlg();
    void markRoute();
    void hideUnmarked();

    bool FibHeap; // what kind of seach

private:
    void doAlgPriorityList();
    void doAlgFibHeaps();

    qint64 ElapsedTime;
};

#endif // DIJKSTRAGRAPHICS_H
