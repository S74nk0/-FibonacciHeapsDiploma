#ifndef DFNODE_H
#define DFNODE_H

#include "edge.h"
#include "nodebase.h"
#include "fibnodebasetemplate.h"

class DFNode : public FibNodeBase<DFNode>, public NodeBase<Edge<DFNode> >
{
public:
    DFNode() : FibNodeBase(), NodeBase() {}
    DFNode(int id, int key) : FibNodeBase(key), NodeBase(id) {}
};

#endif // DFNODE_H
