#include "fibnodebase.h"

FibNodeBase::FibNodeBase() : Child(0), Prev(this), Next(this), Parent(0), key(-1), degree(0), mark(false)
{}

FibNodeBase::FibNodeBase(int k) : Child(0), Prev(this), Next(this), Parent(0), key(k), degree(0), mark(false)
{}

FibNodeBase::FibNodeBase(int k, int d, bool m) : Child(0), Prev(this), Next(this), Parent(0), key(k), degree(d), mark(m)
{}

void FibNodeBase::insertAfter(FibNodeBase *newFNode)
{
    newFNode->Next = this->Next;
    newFNode->Prev = this;
    this->Next->Prev = newFNode;
    this->Next = newFNode;
}

void FibNodeBase::insertBefore(FibNodeBase *newFNode)
{
    newFNode->Prev = this->Prev;
    newFNode->Next = this;
    this->Prev->Next = newFNode;
    this->Prev = newFNode;
}

bool FibNodeBase::contains(FibNodeBase *x)
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

bool FibNodeBase::unlink() // FNode not derstroyed, returns
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

void FibNodeBase::unChild()
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

void FibNodeBase::makeChild(FibNodeBase *child)
{
    this->Child = child;
    child->Parent = this;
}

