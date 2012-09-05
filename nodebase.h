#ifndef NODEBASE_H
#define NODEBASE_H

#include "DijkstraEnumStates.h"

template <class EdgeTemplate>
class NodeBase
{
public:
    NodeBase() : nodeId(0), state(UNLABELED), prevScaned(0) {}
    NodeBase(int id) : nodeId(id), state(UNLABELED), prevScaned(0) {}

    int nodeId;

    State state;
    NodeBase *prevScaned; // prevous scanned

    QVector<EdgeTemplate *> fromEdges; // start
    QVector<EdgeTemplate *> toEdges; // end
};

#endif // NODEBASE_H
