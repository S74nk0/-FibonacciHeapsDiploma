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


private:
    Node reflect; // reflect is for function overloading (reflection workaround)
    int Parent(int i) {
        return (int)(i/2);
    }
    int indexOf(std::vector<DNode *> &Q, DNode *node) {
        int start = 0;
        int end = (int)Q.size();
        --end;

        while(start <= end) {
            if(Q[start] == node)
                return start;
            if(Q[end] == node)
                return end;

            ++start;
            --end;
        }
        return -1; // should never happen in our case
    }

protected:
    // START graph
    QVector<EdgeTemplate *> Edges;
    QVector<Node *> Nodes;
    // END graph

    void doAlg(DNode); // daj mogoce raje inline
    void doAlg(DFNode); // daj mogoce raje inline
};

#endif // DIJKSTRAALGORITHM_H
