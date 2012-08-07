#ifndef NODEBASE_H
#define NODEBASE_H

#include "DijkstraEnumStates.h"

template <class EdgeTemplate>
class NodeBase
{
public:
    NodeBase() : nodeId(0), key(0), state(UNLABELED), prev(0) {}
    NodeBase(int key) : nodeId(-1), key(key), state(UNLABELED), prev(0) {}
    NodeBase(int id, int key) : nodeId(id), key(key), state(UNLABELED), prev(0) {}

    int nodeId;
    int key;
    State state;
    NodeBase *prev; // prevous scanned

    QVector<EdgeTemplate *> fromEdges; // start
    QVector<EdgeTemplate *> toEdges; // end
};

#endif // NODEBASE_H
