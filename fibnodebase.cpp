#include "fibnodebase.h"

template <class Derived>
FibNodeBase<Derived>::FibNodeBase() : Child(0), Prev(this), Next(this), Parent(0), key(-1), degree(0), mark(false)
{}

template <class Derived>
FibNodeBase<Derived>::FibNodeBase(int k) : Child(0), Prev(this), Next(this), Parent(0), key(k), degree(0), mark(false)
{}

template <class Derived>
FibNodeBase<Derived>::FibNodeBase(int k, int d, bool m) : Child(0), Prev(this), Next(this), Parent(0), key(k), degree(d), mark(m)
{}

template <class Derived>
void FibNodeBase<Derived>::insertAfter(FibNodeBase *newFNode)
{
    newFNode->Next = this->Next;
    newFNode->Prev = this;
    this->Next->Prev = newFNode;
    this->Next = newFNode;
}

template <class Derived>
void FibNodeBase<Derived>::insertBefore(FibNodeBase *newFNode)
{
    newFNode->Prev = this->Prev;
    newFNode->Next = this;
    this->Prev->Next = newFNode;
    this->Prev = newFNode;
}

template <class Derived>
bool FibNodeBase<Derived>::contains(FibNodeBase *x)
{
    FibNodeBase *tmp = this->Next;
    while(this != tmp)
    {
        if(tmp == x)
            return true;

        tmp = tmp->Next;
    }

    return false;
}

template <class Derived>
bool FibNodeBase<Derived>::unlink() // FNode not derstroyed, returns
{
    if(this->Next == this)
    {
        return true;
    }
    else
    {
        this->Next->Prev = this->Prev;
        this->Prev->Next = this->Next;

        return false;
    }
}

template <class Derived>
void FibNodeBase<Derived>::unChild()
{
    if(this->Parent != 0)
    {
        if(this->Parent->Child == this) // ce je trenutni otrok kazalec na otroka
        {
            this->Parent->Child = this->Next;
        }
        if(this->Next == this) // zadnji otrok
        {
            this->Parent->Child = 0;
        }

        (void)this->unlink();
        this->Next = this;
        this->Prev = this;

        this->Parent->degree--;
        this->Parent = 0; // 3. korak pokrit
    }
}

template <class Derived>
void FibNodeBase<Derived>::makeChild(FibNodeBase *child)
{
    this->Child = child;
    child->Parent = this;
}
