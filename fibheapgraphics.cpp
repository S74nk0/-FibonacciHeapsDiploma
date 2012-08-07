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
    if(!Nodes.removeOne(ret) && !Nodes.isEmpty())
        qDebug("Nodes remove error");
    this->unlinkEdges();
    if(!Edges.isEmpty())
    {
        delete Edges.last();
        Edges.pop_back();
    }
    this->linkEdges();

    return ret;
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
            Edges[edgeIndex++]->setNodes(node->parent(), node);
    }

    GraphicsFibNode *start = 0;
    if(this->LastNode)
        start = this->LastNode->next();

    while (start != this->LastNode) {
        Edges[edgeIndex++]->setNodes(start, start->next() );
        start = start->next();
    }
}

