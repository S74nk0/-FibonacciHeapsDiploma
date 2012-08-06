#include "fibheapgraphics.h"

//FibHeapGraphics::FibHeapGraphics()
//{}

GraphicsFibNode *FibHeapGraphics::Insert(int key)
{
    GraphicsFibNode *tmpLast = this->LastNode;
    GraphicsFibNode *x = new GraphicsFibNode(key);
    FibHeapBase::Insert(x);//Insert(x);
    Nodes << x;
    if(n > 1) {
        Edges << new GraphicsFibEdge(tmpLast, x);
    }
    return x;
}

GraphicsFibNode *FibHeapGraphics::ExtractMin(int fake)
{
    GraphicsFibNode *ret = FibHeapBase::ExtractMin(false);
    //Update the lists
    if(!Nodes.removeOne(ret))
        qDebug("Nodes remove error");
    this->unlinkEdges();
    if(!Edges.isEmpty())
    {
        delete Edges.last();
        Edges.pop_back();
    }
    this->linkEdges();
}

void FibHeapGraphics::unlinkEdges()
{
    foreach(GraphicsFibEdge *edge, Edges)
    {
        if(!edge->unlink())
            qDebug("FibHeapGraphics::unlinkEdges -> unlink error!");
    }
}

void FibHeapGraphics::linkEdges()
{
    int edgeIndex = 0;
    foreach(GraphicsFibNode *node, Nodes)
    {
        if(node->Parent != 0)
            Edges[edgeIndex++]->setNodes(static_cast<GraphicsFibNode *>(node->Parent), node);
    }

    GraphicsFibNode *start = static_cast<GraphicsFibNode *>(this->LastNode->Next);
    while (start != this->LastNode) {
        Edges[edgeIndex++]->setNodes(start,
                                     static_cast<GraphicsFibNode *>(start->Next) );
        start = static_cast<GraphicsFibNode *>(start->Next);
    }
}

