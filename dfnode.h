#ifndef DFNODE_H
#define DFNODE_H

#include "edge.h"
#include "nodebase.h"
#include "fibnodebasetemplate.h"

class DFNode : public FibNodeBase<DFNode>, public NodeBase<Edge<DFNode> >
{
public:
    DFNode() : FibNodeBase(), NodeBase() {}
    DFNode(int id, int key) : FibNodeBase(), NodeBase(id, key) {}

    //dummdy functions to satisfy the template (there is probably a better way but this is for now the easiest way and with no pefrormance penaulty (extremaley small if any, probabley none))
    inline void setStates() const {}
    inline void update() const {}

};

#endif // DFNODE_H
