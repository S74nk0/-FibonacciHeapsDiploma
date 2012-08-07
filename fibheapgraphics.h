#ifndef FIBHEAPGRAPHICS_H
#define FIBHEAPGRAPHICS_H

#include "fibheapbasetemplate.h"
#include "graphicsfibnode.h"
#include "graphicsfibedge.h"

class FibHeapGraphics : public FibHeapBase<GraphicsFibNode>
{
public:
    GraphicsFibNode *Insert(int key);
    GraphicsFibNode *ExtractMin(int fake);

    void unlinkEdges();
    void linkEdges();

private:
    QList<GraphicsFibEdge *> Edges;
    QList<GraphicsFibNode *> Nodes;
};

#endif // FIBHEAPGRAPHICS_H
