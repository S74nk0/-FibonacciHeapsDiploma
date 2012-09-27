#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H

#include "dnode.h"
#include "fibheapdijkstra.h"

#include <QString>
#include <QFile>
#include <limits>


template <class Node, class EdgeTemplate>
class DijkstraAlgorithm
{

public:
    DijkstraAlgorithm();
    ~DijkstraAlgorithm();

    void loadGraph(QString &fileName);
    //    void loadGraph(QString fileName);
    void doAlg();
    void printResaults();

    void setIndex(int index) { sIndex = index; }
    int getNodeCount() { return Nodes.count(); }

private:
    Node reflect; // reflect is for function overloading (reflection workaround)
    int sIndex;

protected:
    // START graph
    QVector<EdgeTemplate *> Edges;
    QVector<Node *> Nodes;
    // END graph

    void doAlg(DNode, int sourceIndex); // daj mogoce raje inline
    void doAlg(DFNode, int sourceIndex); // daj mogoce raje inline
};

#endif // DIJKSTRAALGORITHM_H
