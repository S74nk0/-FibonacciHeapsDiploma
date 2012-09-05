#include "dijkstraalgorithm.h"

#include <QStringList>
#include <QtAlgorithms>


// LessThan funkcija za q sort pride kot friend funkcija
template <class Node>
bool keyLessThan(const Node *n1, const Node *n2)
{
    return n1->key < n2->key;
}

class PrQue {
public:
    PrQue() : heap_size(0) {}

    int heap_size;
    QList<DNode *> A;

    int parent(int i) {
        return (int)(i/2);
    }

    int left(int i) {
        return 2*i;
    }

    int right(int i) {
        return 2*i+1;
    }

    void MinHeapify(int i) {
        int l = left(i);
        int r = right(i);

        int smallest = -1;

        if(l < heap_size/*A.size()*/ && A[l] < A[i]) {
            smallest = l;
        }
        else {
            smallest = i;
        }
        if(r < heap_size/*A.size()*/ && A[r] < A[smallest] ) {
            smallest = r;
        }
        if(smallest != i) {
            A.swap(i, smallest);
            MinHeapify(smallest);
        }
    }

    void BuildMinHeap() {
        heap_size = A.size();
        for(int i=(int)(A.size()/2); i>=0; --i ) { // 0
            MinHeapify(i);
        }
    }

    void HeapSort() {
        BuildMinHeap();
        for(int i=A.size()-1; i>=1; --i) { // 1
            A.swap(0,i);
            --heap_size;
            MinHeapify(0);
        }
    }


    DNode *HeapExtractMin() {
        if(heap_size < 1) {
            qDebug("heap uderflow");
            return 0;
        }
        DNode *min = A.takeFirst();
//        A[0] = A[heap_size-1];
        heap_size = heap_size-1;
        MinHeapify(1);
        return min;
    }

    void HeapDecreaseKey(int i, int key) {
        if(key > A[i]->key) {
            qDebug("new key is larger");
            return;
        }
        A[i]->key = key;
        while(i > 1 && A[parent(i)] > A[i]) { // 0
            A.swap(i, parent(i));
            i = parent(i);
        }
    }

    void MinHeapInsert(DNode *node, int key) {
        ++heap_size;
        A.push_back(node);
        HeapDecreaseKey(heap_size-1, key);
    }

    void HeapMinimum() {

    }
};

// END heapsort binary heap


//DijkstraAlgorithm

template <class Node, class EdgeTemplate>
DijkstraAlgorithm<Node, EdgeTemplate>::DijkstraAlgorithm()
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

    doAlg(this->reflect);
}

template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::printResaults()
{
    Node *tmp = Nodes[0];
    qDebug("distance price: "+QString::number(tmp->key).toAscii());
    while(tmp)
    {
        QString str = QString::number(tmp->nodeId) + " - ";
        qDebug(str.toAscii());
        tmp = static_cast<Node *>(tmp->prevScaned);
    }
}


template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::doAlg(DNode)
{
    //start node, iz njega razvejemo drevo poti
    int sourceIndex = Nodes.size()-1;
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;

    QList<DNode *> S;
    QList<DNode *> Q = Nodes.toList(); // prednostna vrsta, nisem cisto preprican ali je dejansko to prednostna vrsta ali

    if(sourceIndex != 0)
        Q.swap(0,sourceIndex);

    DNode *take = 0;
    int sortEndIndex = 1;
    while(!Q.empty())
    {
        sortEndIndex = 1;
        DNode *u = Q.takeFirst(); // extract min
        S << u;

        u->state = SCANNED;

        take = 0;
        for(int i=0; i<u->toEdges.size(); ++i)
        {

            if(u->toEdges[i]->endNode()->state != SCANNED)
            {
                int altDistance = u->key + u->toEdges[i]->getPrice();
                if(u->toEdges[i]->endNode()->state == UNLABELED)
                {
                    u->toEdges[i]->endNode()->state = LABELED;
                    u->toEdges[i]->endNode()->prevScaned = u;
                    u->toEdges[i]->endNode()->key = altDistance;
                    //fibheap insert Node
                }
                else if(altDistance < u->toEdges[i]->endNode()->key)
                {
                    u->toEdges[i]->endNode()->key = altDistance; // fib heap decrease key
                    u->toEdges[i]->endNode()->prevScaned = u;
                }

                take = Q.takeAt(Q.indexOf(u->toEdges[i]->endNode()));
                Q.push_front(take);
                ++sortEndIndex;
            }
        }
        qSort(Q.begin(), Q.begin()+sortEndIndex, keyLessThan<DNode>); // sortira po vrsi
    }

    printResaults();
}

template <class Node, class EdgeTemplate>
void DijkstraAlgorithm<Node, EdgeTemplate>::doAlg(DFNode)
{
    //start node, iz njega razvejemo drevo poti
    int sourceIndex = Nodes.size()-1;
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;


    FibHeapDijkstra heap;

    QList<DFNode *> S;
    heap.Insert(Nodes[sourceIndex]);

    while(heap.Min() != 0)
    {

        // velika pohitritev
        DFNode *u = heap.ExtractMin(); // extract min
        S << u;

        u->state = SCANNED;

        for(int i=0; i<u->toEdges.size(); ++i)
        {

            if(u->toEdges[i]->endNode()->state != SCANNED)
            {
                int altDistance = u->key + u->toEdges[i]->getPrice();
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

    printResaults();
}
