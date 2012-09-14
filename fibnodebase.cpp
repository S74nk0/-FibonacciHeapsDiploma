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
FibNodeBase<Derived>::~FibNodeBase()
{
    this->Child = 0;
    this->Prev = 0;
    this->Next = 0;
    this->Parent = 0;
}

template <class Derived>
void FibNodeBase<Derived>::insertAfter(FibNodeBase *newFNode)
{
    newFNode->Next = this->Next;
    newFNode->Prev = this;
    this->Next->Prev = newFNode;
    this->Next = newFNode;
}

template <class Derived>
void FibNodeBase<Derived>::insertAfter(FibNodeBase *newFNode, FibNodeBase *newFNodeLast)
{
    if(newFNode != newFNodeLast)
    {
        newFNodeLast->Next = this->Next;
        this->Next->Prev = newFNodeLast;
        newFNode->Prev = this;
        this->Next = newFNode;
    }
    else
    {
        insertAfter(newFNode);
    }
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
void FibNodeBase<Derived>::insertBefore(FibNodeBase *newFNode, FibNodeBase *newFNodeLast)
{
    if(newFNode != newFNodeLast)
    {
        newFNode->Prev = this->Prev;
        this->Prev->Next = newFNode;
        newFNodeLast->Next = this;
        this->Prev = newFNodeLast;
    }
    else
    {
        insertBefore(newFNode);
    }
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
void FibNodeBase<Derived>::unlink2()
{
    this->Next->Prev = this->Prev;
    this->Prev->Next = this->Next;
    this->Next = this;
    this->Prev = this;
}

template <class Derived>
void FibNodeBase<Derived>::unChild()
{
    if(this->Parent)
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

template <class Derived>
void FibNodeBase<Derived>::makeChildLink(FibNodeBase *child)
{
    child->Parent = this;
    if(!this->Child)
    {
        this->Child = child;
    }

    child->Next = this->Child;
    child->Prev = this->Child->Prev;
    this->Child->Prev->Next = child;
    this->Child->Prev = child;

    ++this->degree;
    child->mark = false;
}
