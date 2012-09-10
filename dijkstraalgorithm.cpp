#include "dijkstraalgorithm.h"

#include <QStringList>
#include <QtAlgorithms>


// LessThan funkcija za q sort pride kot friend funkcija
template <class Node>
bool keyLessThan(const Node *n1, const Node *n2)
{
    return n1->key < n2->key;
}

template<class Node2>
class PrQue {
public:
    PrQue() {}
    PrQue(QList<Node2 *> a) : A(a) {}
    QList<Node2 *> A;

    int parent(int i) {
            return (int)((i-1)/2);
    }

    int left(int i) {
            return 2*(i+1)-1;
    }

    int right(int i) {
            return 2*(i+1);
    }

    void MinHeapify(int i) {
        if(i >= A.count()-1)
            return;

        int iPlus = i+1;
        int l = left(i);
        int r = right(i);

        int smallest = -1;

        if(l < A.size() && A[l]->key < A[i]->key) {
            smallest = l;
        }
        else {
            smallest = i;
        }
        if(r < A.size() && A[r]->key < A[smallest]->key ) {
            smallest = r;
        }
        if(smallest != i) {
            A.swap(i, smallest);
            MinHeapify(smallest);
        }
        else
            MinHeapify(iPlus);
    }

    void BuildMinHeap() {
        for(int i=(int)(A.size()/2); i>=0; --i ) { // 0
            MinHeapify(i);
        }
    }

    void HeapSort() {
        BuildMinHeap();
        for(int i=A.size()-1; i>=1; --i) { // 1
            A.swap(0,i);
            MinHeapify(0);
        }
    }

    Node2 *ExtractMin() {
        if(A.count() < 1) {
            qDebug("heap uderflow");
            return 0;
        }
        Node2 *min = A.takeFirst();
        MinHeapify(0); //

        return min;
    }

    void DecreaseKey(int i, int key) {
        if(key > A[i]->key) {
            qDebug("new key is larger");
            return;
        }
        A[i]->key = key;
        while(i > 0 && A[parent(i)]->key >= A[i]->key) { // 0
            A.swap(i, parent(i));
            i = parent(i);
        }
    }

    void DecreaseKey(Node2 *node, int key) {
        if(key > node->key) {
            qDebug("new key is larger");
            return;
        }
        int i = A.indexOf(node);
        A[i]->key = key;
        while(i > 0 && A[parent(i)]->key > A[i]->key) { // 0
            A.swap(i, parent(i));
            i = parent(i);
        }
    }

    void Insert(Node2 *node) {
        A.push_back(node);
        DecreaseKey(A.count()-1, node->key);
    }

    bool empty() const
    {
        return A.empty();
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

    doAlg(this->reflect); // original

////#define FIBONACCI
//#ifdef FIBONACCI
//    FibHeapDijkstra heap;
//#else
//    PrQue<Node> heap;
//#endif

//    //start node, iz njega razvejemo drevo poti
//    int sourceIndex = Nodes.size()-1;//Nodes.size()-50;//Nodes.size()-1;
//    Nodes[sourceIndex]->key = 0;
//    Nodes[sourceIndex]->state = LABELED;

//    heap.Insert(Nodes[sourceIndex]);

//    Node *u = 0;
//    while(heap.empty())
//    {
//        u = heap.ExtractMin(); // extract min

//        u->state = SCANNED;

//        for(int i=0; i<u->toEdges.size(); ++i)
//        {
//            if(u->toEdges[i]->endNode()->state != SCANNED)
//            {
//                int altDistance = u->key + u->toEdges[i]->getPrice();
//                if(u->toEdges[i]->endNode()->state == UNLABELED)
//                {
//                    u->toEdges[i]->endNode()->state = LABELED;
//                    u->toEdges[i]->endNode()->prevScaned = u;
//                    u->toEdges[i]->endNode()->key = altDistance;
//                    heap.Insert(u->toEdges[i]->endNode());
//                }
//                else if(altDistance < u->toEdges[i]->endNode()->key)
//                {
//                    heap.DecreaseKey(u->toEdges[i]->endNode(), altDistance);
//                    u->toEdges[i]->endNode()->prevScaned = u;
//                }
//            }
//        }
//    }

//    printResaults();
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
    int sourceIndex = Nodes.size()-50;//Nodes.size()-1;
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;

//    QList<DNode *> S;
    PrQue<DNode> Q;

    Q.Insert(Nodes[sourceIndex]);

    DNode *u = 0;
    while(!Q.empty())
    {
        u = Q.ExtractMin();

//        S << u;

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
                    Q.Insert(u->toEdges[i]->endNode());
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
void DijkstraAlgorithm<Node, EdgeTemplate>::doAlg(DFNode)
{
    //start node, iz njega razvejemo drevo poti
    int sourceIndex = Nodes.size()-1;//Nodes.size()-50;//Nodes.size()-1;
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;

    FibHeapDijkstra heap;

    QList<DFNode *> S;

    heap.Insert(Nodes[sourceIndex]);

    DFNode *u = 0;
    while(heap.Min() != 0)
    {
        // velika pohitritev
        u = heap.ExtractMin(); // extract min
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

//    qDebug(QString::number(dKey).toAscii());
    printResaults();
}
