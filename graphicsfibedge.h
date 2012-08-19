#ifndef GRAPHICSFIBEDGE_H
#define GRAPHICSFIBEDGE_H

#include "graphicsfibnode.h"

class GraphicsFibEdge : public GraphicsEdge<GraphicsFibNode>
{
public:
    GraphicsFibEdge(GraphicsFibNode *start, GraphicsFibNode *end) :
        GraphicsEdge(start, end) {}
};

#endif // GRAPHICSFIBEDGE_H
