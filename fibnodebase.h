#ifndef FIBNODEBASE_H
#define FIBNODEBASE_H


class FibNodeBase
{
public:
    FibNodeBase();
    FibNodeBase(int k);
    FibNodeBase(int k, int d, bool m);

    FibNodeBase *Child;
    FibNodeBase *Prev;
    FibNodeBase *Next;
    FibNodeBase *Parent;

    int key; // ta vrednost se hrani v NodeBase
    int degree;
    bool mark;

    void insertAfter(FibNodeBase *newFNode);
    void insertBefore(FibNodeBase *newFNode);
    bool contains(FibNodeBase *x);
    bool unlink(); // FNode not derstroyed, returns
    void unChild();
    void makeChild(FibNodeBase *child);
};

#endif // FIBNODEBASE_H
