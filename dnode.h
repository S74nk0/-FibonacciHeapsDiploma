#ifndef DNODE_H
#define DNODE_H

#include "edge.h"
#include "nodebase.h"

class DNode : public NodeBase<Edge<DNode> >
{
public:
    DNode() : NodeBase(), key(-1) {}
    DNode(int id, int key) : NodeBase(id), key(key) {}
    int key;

    bool operator<(const DNode& b) {
      return this->key < b.key;
    }
};

#endif // DNODE_H
