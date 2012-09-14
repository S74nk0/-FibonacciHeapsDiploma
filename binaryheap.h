#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include "dnode.h"

//template<class Node>
class BinaryHeap {
public:
    BinaryHeap() {}
    BinaryHeap(QList<DNode *> a) : A(a) {}
    QList<DNode *> A;

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

    DNode *ExtractMin() {
        if(A.count() < 1) {
            qDebug("heap uderflow");
            return 0;
        }
        DNode *min = A.takeFirst();
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

    void DecreaseKey(DNode *node, int key) {
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

    void Insert(DNode *node, int key) {
        A.push_back(node);
        DecreaseKey(A.count()-1, key);
    }

    bool empty() const
    {
        return A.empty();
    }
};

// END heapsort binary heap

#endif // BINARYHEAP_H
