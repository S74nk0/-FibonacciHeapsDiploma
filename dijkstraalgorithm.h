#ifndef DIJKSTRAALGORITHM_H
#define DIJKSTRAALGORITHM_H

#include "dnode.h"
#include "fibheapdijkstra.h"

#include <QString>
#include <QFile>
#include <limits>

template <class Node>
class DijkstraAlgorithm
{

public:
    DijkstraAlgorithm();
    ~DijkstraAlgorithm();

    void loadGraph(QString &fileName);
    //    void loadGraph(QString fileName);
    void doAlg();
    void printResaults();


private:
    Node reflect; // reflect is for function overloading (reflection workaround)
    // START graph
    QVector<Edge<Node> *> Edges;
    QVector<Node *> Nodes;
    // END graph

    void doAlg(DNode); // daj mogoce raje inline
    void doAlg(DFNode); // daj mogoce raje inline
};

#endif // DIJKSTRAALGORITHM_H
