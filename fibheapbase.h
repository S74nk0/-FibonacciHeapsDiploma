#ifndef FIBHEAPBASE_H
#define FIBHEAPBASE_H

#include <limits>
#include <vector> // temporary ?
#include "QDebug"

template<class Node>
class FibHeapBase
{
public:

    //19.2
    FibHeapBase(); // MakeFibHeap
    Node *Insert(int key);
    void Insert(Node *newNode);
    Node *Min() const;
    FibHeapBase<Node> *Union(FibHeapBase *H2);//    Uniting two Fibonacci heaps #fixed!
    Node *ExtractMin(bool deleteFunc = false);//Extracting the minimum FNode, deleteFunc ce klicemo iz delete zaradi strukture


    //19.3
    void DecreaseKey(Node *x, int k);
    void Delete(Node *x);

//private: // komentiraj zacasno
protected:
    Node *min;
    int n;
    Node *LastNode;

    void insertLast(Node *newNode);

    //19.2
    void Consolidate(); // # fixed!
    void Link(Node *y, Node *x);

    //19.3
    void Cut(Node *x/*, FNode *y*/);
    void CascadingCut(Node *y);
};

#endif // FIBHEAPBASE_H
