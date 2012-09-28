#include "dijkstraalgorithm.h"

#include <QStringList>
#include <QtAlgorithms>
#include "binaryheap.h"

// LessThan funkcija za q sort pride kot friend funkcija
template <class Node>
bool keyLessThan(const Node *n1, const Node *n2)
{
    return n1->key < n2->key;
}


//DijkstraAlgorithm

template <class Node, class EdgeTemplate>
DijkstraAlgorithm<Node, EdgeTemplate>::DijkstraAlgorithm() : sIndex(-1)
{
}

template <class Node, class EdgeTemplate>
DijkstraAlgorithm<Node, EdgeTemplate>::~DijkstraAlgorithm()
{
    for(int i=0; i<Nodes.size(); ++i)
        delete Nodes[i];

    for(int i=0; i<Edges.size(); ++i)
        delete Edges[i];
}

template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::loadGraph(QString &fileName)
{
    QFile graph(fileName);
    QString tempRead;

    int intMax = std::numeric_limits<int>::max();

    if (!graph.open(QIODevice::ReadOnly))
    {
        qDebug("Error oppening graph file in DijkstraAlgorithm::loadGraph()");
        return;
    }

    tempRead = graph.readLine();
    int nodesSize = tempRead.toInt(); // prva linija bi naj vedno blo stevilo vseh vozlisc

    // inicializacija
    Node *newNode = 0;
    for(int i = 0; i < nodesSize; ++i)
    {
        newNode = new Node(i,/*-1*/intMax);
        Nodes.push_back(newNode);
    }

    EdgeTemplate *newEdge = 0;
    QStringList vals;
    while(!graph.atEnd())
    {
        tempRead = graph.readLine();
        vals = tempRead.split(' ');

        if(vals.size() < 3)
        {
            qDebug("ERROR VALS");
            return;
        }

        int start = vals.at(0).toInt();
        int end = vals.at(1).toInt();
        int price = vals.at(2).toInt();

        newEdge = new EdgeTemplate(Nodes[start], Nodes[end], price);
        Edges.push_back(newEdge);
    }

    graph.close();
}

template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::doAlg()
{
    //inicializacija je izvedena v branju grafa
    if(Nodes.empty())
    {
        qDebug("Not initialized!");
        return;
    }

    if(sIndex == -1)
        doAlg(this->reflect, Nodes.size()-1);
    else
        doAlg(this->reflect, sIndex);
}

template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::printResaults()
{
    Node *tmp = Nodes[0];
    qDebug("distance price: "+QString::number(tmp->key).toAscii());
//    while(tmp)
//    {
//        QString str = QString::number(tmp->nodeId) + " - ";
//        qDebug(str.toAscii());
//        tmp = static_cast<Node *>(tmp->prevScaned);
//    }
}


template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::doAlg(DNode, int sourceIndex)
{
    //start node, iz njega razvejemo drevo poti
//    int sourceIndex = Nodes.size()-1;//Nodes.size()-1;
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;

//    QList<DNode *> S;
    BinaryHeap Q;

    Q.BuildMinHeap();
    Q.Insert(Nodes[sourceIndex], 0);

    DNode *u = 0;
    int altDistance = 0;
    while(!Q.empty())
    {
        u = Q.ExtractMin();

//        S << u;

        u->state = SCANNED;

        for(int i=0; i<u->toEdges.size(); ++i)
        {
            if(u->toEdges[i]->endNode()->state != SCANNED)
            {
                altDistance = u->key + u->toEdges[i]->getPrice();
                if(u->toEdges[i]->endNode()->state == UNLABELED)
                {
                    u->toEdges[i]->endNode()->state = LABELED;
                    u->toEdges[i]->endNode()->prevScaned = u;
                    Q.Insert(u->toEdges[i]->endNode(), altDistance);
                }
                else if(altDistance < u->toEdges[i]->endNode()->key)
                {
                    Q.DecreaseKey(u->toEdges[i]->endNode(), altDistance);
                    u->toEdges[i]->endNode()->prevScaned = u;
                }
            }
        }
    }

//    printResaults();

}

template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::doAlg(DFNode, int sourceIndex)
{
    //sourceIndex, iz njega razvejemo drevo poti
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;

    FibHeapDijkstra heap;

//    QList<DFNode *> S;

    heap.Insert(Nodes[sourceIndex]);

    DFNode *u = 0;
    int altDistance = 0;
    while(heap.Min() != 0)
    {
        // velika pohitritev
        u = heap.ExtractMin(); // extract min
//        S << u;

        u->state = SCANNED;

        for(int i=0; i<u->toEdges.size(); ++i)
        {
            if(u->toEdges[i]->endNode()->state != SCANNED)
            {
                altDistance = u->key + u->toEdges[i]->getPrice();
                if(u->toEdges[i]->endNode()->state == UNLABELED)
                {
                    u->toEdges[i]->endNode()->state = LABELED;
                    u->toEdges[i]->endNode()->prevScaned = u;
                    u->toEdges[i]->endNode()->key = altDistance;
                    heap.Insert(u->toEdges[i]->endNode());
                }
                else if(altDistance < u->toEdges[i]->endNode()->key)
                {
                    heap.DecreaseKey(u->toEdges[i]->endNode(), altDistance);
                    u->toEdges[i]->endNode()->prevScaned = u;
                }
            }
        }
    }

//    qDebug(QString::number(dKey).toAscii());
//    printResaults();
}
