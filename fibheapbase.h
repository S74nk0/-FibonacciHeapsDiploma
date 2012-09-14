#ifndef FIBHEAPBASE_H
#define FIBHEAPBASE_H

#include <limits>
#include "QDebug"

//xml and file
#include <QDomDocument>
#include <QFile>
#include <QTextStream>

#include "cdlist.h"

template<class Node>
class FibHeapBase
{
public:
    //19.2
    FibHeapBase(); // MakeFibHeap
    ~FibHeapBase();
    Node *Insert(int key);
    void Insert(Node *newNode);
    Node *Min() const;
    FibHeapBase<Node> *Union(FibHeapBase *H2);//    Uniting two Fibonacci heaps #fixed!
    Node *ExtractMin();//Extracting the minimum FNode, deleteFunc ce klicemo iz delete zaradi strukture


    //19.3
    void DecreaseKey(Node *x, int k);
    void Delete(Node *x);

    //O
    void Generate(int numOfFNodes, int randRange = RAND_MAX);
    void ExportHeap(QString &fileName);
    void ImportHeap(QString &fileName);

    inline Node *empty() {
        return min;
    }

protected:
    Node *min;
    int n;
    CDList<Node> rootList;

    inline void linkNeighbours(Node *next, Node *prev) const;

    //19.2
    void Consolidate(); // # fixed!
    inline void Link(Node *y, Node *x);

    //19.3
    inline void Cut(Node *x/*, Node *y*/);
    void CascadingCut(Node *y);

    //O
    int InsertElements(QDomDocument &document, QDomElement &root, Node *firstNode); // vrne index minimalnega vozlisca
    void InsertElement(QDomDocument &document, QDomElement &root, Node *node);
    QDomElement createElement(QDomDocument &document, Node *node);

    void NodesFromDomRoot(QDomElement &root);
    void NodesFromDomEl(QDomElement &elem, Node *NodeParent);
    Node *getNode(QDomElement &elem);

};

#endif // FIBHEAPBASE_H
