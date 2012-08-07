#ifndef FIBHEAPGRAPHICS_H
#define FIBHEAPGRAPHICS_H

#include "fibheapbasetemplate.h"
#include "graphicsfibnode.h"
#include "graphicsfibedge.h"

class FibHeapGraphics : public FibHeapBase<GraphicsFibNode>
{
public:
    ~FibHeapGraphics();
    GraphicsFibNode *Insert(int key);
    GraphicsFibNode *ExtractMin(int fake);
    FibHeapGraphics *Union(FibHeapGraphics *H2);

    void unlinkEdges();
    void linkEdges();
    void setStates();
    void updateEdges();
    void clear();

    void animate(int timemil);
    void animateInsert();
    void setFirstPositions();
    void saveCurrentPositions();
    void clearPositions();

    bool blockComponents();

    QPointF referencePoint;

    QList<GraphicsFibEdge *> edges() const;
    QList<GraphicsFibNode *> nodes() const;

private:
    QList<GraphicsFibEdge *> Edges;
    QList<GraphicsFibNode *> Nodes;
};

#endif // FIBHEAPGRAPHICS_H
