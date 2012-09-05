#ifndef FIBNODEBASE_H
#define FIBNODEBASE_H

template <class Derived>
class FibNodeBase
{
public:
    FibNodeBase();
    FibNodeBase(int k);
    FibNodeBase(int k, int d, bool m);
    ~FibNodeBase();

    FibNodeBase *Child;
    FibNodeBase *Prev;
    FibNodeBase *Next;
    FibNodeBase *Parent;

    int key;
    int degree;
    bool mark;

    inline Derived *child() const { return static_cast<Derived *>(this->Child); }
    inline Derived *parent() const { return static_cast<Derived *>(this->Parent); }
    inline Derived *next() const { return static_cast<Derived *>(this->Next); }
    inline Derived *prev() const { return static_cast<Derived *>(this->Prev); }

    inline void insertAfter(FibNodeBase *newFNode);
    inline void insertBefore(FibNodeBase *newFNode);
    bool contains(FibNodeBase *x);
    inline bool unlink(); // FNode not derstroyed, returns
    inline void unlink2();
    inline void unChild();
    inline void makeChild(FibNodeBase *child);
    inline void makeChildLink(FibNodeBase *child);
};

#endif // FIBNODEBASE_H
