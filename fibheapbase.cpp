#include "fibheapbase.h"

#include <math.h>

template<class Node>
FibHeapBase<Node>::FibHeapBase() : min(0), n(0), LastNode(0) //MakeFibHeap
{
}

template<class Node>
Node *FibHeapBase<Node>::Insert(int key)
{
    Node *x = new Node(key);
    this->Insert(x);
    return x;
}

template<class Node>
void FibHeapBase<Node>::Insert(Node *newNode)
{
    if(this->min == 0)
    {
        this->min = newNode;
        this->LastNode = newNode;
    }
    else
    {
        this->insertLast(newNode);
        if(newNode->key < this->min->key)
        {
            this->min = newNode;
        }
    }
    ++this->n;
}

template<class Node>
Node * FibHeapBase<Node>::Min() const
{
    return this->min;
}

template<class Node>
FibHeapBase<Node> *FibHeapBase<Node>::Union(FibHeapBase *H2)
{
    FibHeapBase *newH = new FibHeapBase();
    newH->min = this->min;
    newH->LastNode = this->LastNode;

//    newH.min->insertEnd(this->LastNode, H2.min); // povezava
    if(this->min != 0 && H2->min != 0)
    {
        Node *FirstNode = this->LastNode->Next;
        Node *H2FirstNode = H2->LastNode->Next;

        this->LastNode->Next = H2FirstNode;
        H2FirstNode->Prev = this->LastNode;

        H2->LastNode->Next = FirstNode;
        FirstNode->Prev = H2->LastNode;

        newH->LastNode = H2->LastNode;
    }

    if( this->min == 0 || (H2->min != 0 && H2->min->key < this->min->key) )
    {
        newH->min = H2->min;
    }

    newH->n = this->n + H2->n;

    return newH;
}

template<class Node>
Node *FibHeapBase<Node>::ExtractMin(bool deleteFunc/* = false*/)
{
    Node *z = this->min;

    if(z != 0)
    {
        Node *ChildListEnd = 0;
        if(z->Child != 0)
        {
//            z->unChildList(); // seznam povezemo z seznamom oceta
            Node *ChildListStart = z->child();
//            Node *ChildListEnd = ChildListStart;
            for(int i = 0; i < z->degree; ++i)
            {
                ChildListStart->Parent = 0;
                ChildListStart = ChildListStart->next();
            }

            ChildListEnd = ChildListStart->prev();

            Node *FirstNode = this->LastNode->next();

            ChildListStart->Prev = this->LastNode;
            this->LastNode->Next = ChildListStart;

            ChildListEnd->Next = FirstNode;
            FirstNode->Prev = ChildListEnd;

            this->LastNode = ChildListEnd;
        }

        if(z->unlink())
        {
            this->min = 0;
            this->LastNode = 0;
        }
        else
        {
            //ce je z = LastNode
            if(z == LastNode)
                LastNode = z->prev();

            this->min = z->next();
            if(this->min->Child != 0 && !deleteFunc && ChildListEnd != 0) // za strukturo (obliko fibHeapa, ni bistveno za kopico sam zgradi jo po moji volji -> lepsa je)
            {
                this->min = ChildListEnd;
            }

            //this part of the code isn't for the alghorithm but for the template to satisfy one function for both graphical node and non graphical
            this->LastNode->next()->setStates();//this->min->setStates(); // the setStates
            //end of template function

            this->Consolidate();
        }
        --this->n;
    }

    return z;
}

//19.3
template<class Node>
void FibHeapBase<Node>::DecreaseKey(Node *x, int k)
{
    if(k > x->key)
    {
        qDebug("ERROR NEW KEY IS GREATER THAN CURRENT KEY");
        return;
    }

    x->key = k;
    x->update(); // for the graphics/visuals nothing to do with the algorithm

    Node *y = x->parent();

    if(y != 0 && x->key < y->key)
    {
        this->Cut(x/*, y*/);
        this->min->setStates(); // for the graphics/visuals nothing to do with the algorithm
        this->CascadingCut(y);
    }

    if(x->key < this->min->key)
    {
        this->min = x;
    }
}

template<class Node>
void FibHeapBase<Node>::Delete(Node *x)
{
    this->DecreaseKey(x, std::numeric_limits<int>::min() );
    Node *deleteNode = this->ExtractMin(true);//static_cast<Node *>( this->ExtractMin(true) );
    delete deleteNode;
}

//private

template<class Node>
void FibHeapBase<Node>::insertLast(Node *newNode)
{
    if(this->LastNode != 0)
    {
        this->LastNode->insertAfter(newNode);
    }
    this->LastNode = newNode;
}

//19.2
template<class Node>
void FibHeapBase<Node>::Consolidate() // # fixed!
{
    double f = log((double) this->n)/ log(2.0);
    int D = (int)(f)+2;//D();
    std::vector<Node * > A;

    for(int i = 0; i < D; ++i)
    {
        A.push_back(0);
    }

    Node *x, *y, *tmp;

    x = this->min;
    do
    {
        int d = x->degree;

        while(A[d] != 0 && x != A[d])
        {
            y = A[d];
            if(x != 0 && y != 0)
            {
                if(x->key > y->key)
                {
                    tmp = x;
                    x = y;
                    y = tmp;
                }
                if(y == this->min)
                    this->min = x;

                this->Link(y, x);// states change
                this->LastNode->next()->setStates();//this->min->setStates(); // again this part is only for the graphical representation and not esential to the algorithm it has no part in the pseudocode in the alghorithm

                if(x->Next == x)
                    this->min = x;
            }

            A[d] = 0;
            ++d;
        }
        A[d] = x;

        x = x->next();
    }while(x != this->min);

    for(int i = 0; i < D; ++i)
    {
        if(A[i] != 0)
        {
            if(A[i]->key < this->min->key || (this->min->key == A[i]->key && A[i]->degree > this->min->degree)) // or v primeru istih kljucev, brez tega inf loop
            {
                this->min = A[i];
            }
        }
    }

    A.clear();
}

template<class Node>
void FibHeapBase<Node>::Link(Node *y, Node *x)
{
    if(y == LastNode)
        LastNode = y->prev();

    y->unlink();

    if(x->Next == x)
    {
        this->min = x;
    }
    y->Next = y;
    y->Prev = y;
    y->Parent = x;

    if(x->Child == 0)
    {
        x->Child = y;
    }

    y->Next = x->Child;
    y->Prev = x->Child->Prev;
    x->Child->Prev->Next = y;
    x->Child->Prev = y;

    if(x->Child->degree < y->degree)
        x->Child = y;

    // lll
    x->degree++;
//    y->Parent = x; // ponavljas se
    y->mark = false;
    //the update fuction is only for the visuals/ graphics and has nothing to do with the algorithm
    y->update(); //
}

//19.3
template<class Node>
void FibHeapBase<Node>::Cut(Node *x/*, Node *y*/) // y nepotreben zaradi unChild funkcije
{
    x->unChild(); // 3. korak pokrit
    this->insertLast(x);
    x->mark = false;
}

template<class Node>
void FibHeapBase<Node>::CascadingCut(Node *y)
{
    Node *z = y->parent();
    if(z != 0)
    {
        if(y->mark == false)
        {
            y->mark = true;
            y->update(); // for the graphics/visuals nothing to do with the algorithm
        }
        else
        {
            this->Cut(y/*, z*/);
            this->min->setStates(); // for the graphics/visuals nothing to do with the algorithm
            this->CascadingCut(z);
        }
    }
}

