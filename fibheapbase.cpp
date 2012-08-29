#include "fibheapbase.h"

#include <math.h>
#include <QTime>

static const double ln = log(2.0);

template<class Node>
FibHeapBase<Node>::FibHeapBase() : min(0), n(0), LastNode(0) //MakeFibHeap
{
}

template<class Node>
FibHeapBase<Node>::~FibHeapBase()
{
    min = 0;
    LastNode = 0;
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

    if(this->min != 0 && H2->min != 0)
    {
        Node *FirstNode = this->LastNode->next();
        Node *H2FirstNode = H2->LastNode->next();

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
            Node *ChildListStart = z->child();
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

#ifdef FIBHEAPGRAPHICS_H
            //this part of the code isn't for the alghorithm but for the template to satisfy one function for both graphical node and non graphical
            this->LastNode->next()->setStates(); // the setStates
            //end of template function
#endif

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

    Node *y = x->parent();

    if(y != 0 && x->key < y->key)
    {
        this->Cut(x/*, y*/);
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
    double f = log( static_cast<double>(this->n) )/ln; // ln(n) = log(n)/log(2.0)
    int D = qRound(f) + 1;//D();

//    Node **A = new Node*[D];
    Node *A[D]; // microoptimization stack

    for(int i = 0; i < D; ++i)
    {
        A[i] = 0;
    }

    Node *x = 0, *y = 0, *tmp = 0;

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
            }

            A[d] = 0;
            ++d;
        }
        A[d] = x;

        x = x->next();
    }while(x != this->min);


    for(int i = 0; i < D; ++i)
    {
        if(A[i])
        {
            if(A[i]->key < this->min->key || (this->min->key == A[i]->key && A[i]->degree < this->min->degree)) // speed up if we set the min node as also th node with the min degree
            {
                this->min = A[i];
            }
        }
    }

//    delete[] A;
}

template<class Node>
void FibHeapBase<Node>::Link(Node *y, Node *x)
{
    if(y == LastNode)
        LastNode = y->prev();


//    if(x->Next == x) // remove this?
//    {
//        this->min = x;
//    }

    y->unlink2();
    x->makeChildLink(y);

#ifdef FIBHEAPGRAPHICS_H
    this->LastNode->next()->setStates(); // again this part is only for the graphical representation and not esential to the algorithm it has no part in the pseudocode in the alghorithm
#endif
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
        }
        else
        {
            this->Cut(y/*, z*/);
            this->CascadingCut(z);
        }
    }
}

//O
template<class Node>
void FibHeapBase<Node>::ExportHeap(QString &fileName)
{
    QString rootTagName = "fibheap";
    QString rootAtribute = "minNode";
    QString rootAtribute2 = "n";
    int minNodeIndex = 0;

    QDomDocument document;

    QDomElement root = document.createElement(rootTagName);
    document.appendChild(root);

    if(this->LastNode != 0)
    {
        Node *FirsRootNode = this->LastNode->next();
        if(FirsRootNode != 0)
            minNodeIndex = InsertElements(document, root, FirsRootNode);
    }

    root.setAttribute(rootAtribute, minNodeIndex);
    root.setAttribute(rootAtribute2, this->n);

    QDomElement r2 = document.documentElement(); // bris

    //Write to file
    QFile compressed(fileName + ".fibh");

    compressed.open(QIODevice::WriteOnly);
    compressed.write(qCompress(document.toByteArray()));
    compressed.close();
}

template<class Node>
int FibHeapBase<Node>::InsertElements(QDomDocument &document, QDomElement &root, Node *firstNode) // vrne index minimalnega vozlisca
{
    int minIndex = 0;
    int returnIndex = 0;

    Node *tempNode = firstNode;
    do {
        QDomElement newRoot = createElement(document, tempNode);
        root.appendChild(newRoot);
        InsertElement(document, newRoot, tempNode->child());

        if(tempNode == this->min)
            returnIndex = minIndex;

        tempNode = tempNode->next();
        minIndex++;
    } while(tempNode != firstNode);

    return returnIndex;
}

template<class Node>
void FibHeapBase<Node>::InsertElement(QDomDocument &document, QDomElement &root, Node *node)
{
    if(node == 0)
        return;

    Node *tempNode = node;
    do {
        QDomElement newRoot = createElement(document, tempNode);
        root.appendChild(newRoot);
        InsertElement(document, newRoot, tempNode->child());

        tempNode = tempNode->next();
    } while(tempNode != node);
}

template<class Node>
QDomElement FibHeapBase<Node>::createElement(QDomDocument &document, Node *node)
{
    QString nodeTag = "node";
    QString atrKey = "key";
    QString atrDegree = "degree";
    QString atrMark = "mark";
    QString markValue = "false";

    if(node->mark)
        markValue = "true";

    QDomElement retElement = document.createElement(nodeTag);
    retElement.setAttribute(atrKey, node->key);
    retElement.setAttribute(atrDegree, node->degree);
    retElement.setAttribute(atrMark, markValue);

    return retElement;
}

template<class Node>
void FibHeapBase<Node>::ImportHeap(QString &fileName)
{
    QString errorMsg;
    int errorLine = 0;
    int errorColumn = 0;

    QDomDocument doc;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!doc.setContent(qUncompress(file.readAll()), &errorMsg, &errorLine, &errorColumn))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();

    NodesFromDomRoot(root);
}

template<class Node>
void FibHeapBase<Node>::NodesFromDomRoot(QDomElement &root)
{
    QDomElement elt = root.firstChildElement();
    QDomElement last = root.lastChildElement();
    QDomElement childElem = elt.firstChildElement();

    Node *tmpNode = getNode(elt);
    NodesFromDomEl(childElem, tmpNode);
    elt = elt.nextSiblingElement();
    this->LastNode = tmpNode;
    this->min = tmpNode;

    int indexMinCount = 1;
    int minIndex = root.attribute("minNode").toInt();
    this->n = root.attribute("n").toInt();

    for (; !elt.isNull(); elt = elt.nextSiblingElement())
    {
        tmpNode = getNode(elt);
        this->LastNode->insertAfter(tmpNode);
        childElem = elt.firstChildElement();
        NodesFromDomEl(childElem, tmpNode);
        this->LastNode = tmpNode;

        if(minIndex == indexMinCount)
            this->min = tmpNode;

        indexMinCount++;
    }
    this->LastNode = tmpNode;
}

template<class Node>
void FibHeapBase<Node>::NodesFromDomEl(QDomElement &elem, Node *NodeParent)
{
    if(elem.isNull())
        return;

    QDomElement elt = elem;
    QDomElement childElem = elt.firstChildElement();
    Node *tmpNode = getNode(elt);
    NodeParent->makeChild(tmpNode);
    NodesFromDomEl(childElem, tmpNode);
    elt = elt.nextSiblingElement();
    Node *Last = tmpNode;

    for(; !elt.isNull(); elt = elt.nextSiblingElement())
    {
        tmpNode = getNode(elt);
        Last->insertAfter(tmpNode);
        childElem = elt.firstChildElement();
        NodesFromDomEl(childElem, tmpNode);
        tmpNode->Parent = NodeParent;


        Last = tmpNode;
    }
}

template<class Node>
Node *FibHeapBase<Node>::getNode(QDomElement &elem)
{
    QString StrKey = "key";
    QString StrDegree = "degree";
    QString StrMark = "mark";
    int key, degree;
    bool mark = false;

    StrKey = elem.attribute(StrKey);
    StrDegree = elem.attribute(StrDegree);
    StrMark = elem.attribute(StrMark);

    if(StrMark == "true")
        mark = true;
    key = StrKey.toInt();
    degree = StrDegree.toInt();

    Node *node = new Node(key,degree,mark);

    return node;
}

template<class Node>
void FibHeapBase<Node>::Generate(int numOfFNodes, int randRange)
{
    QTime mid(0,0,0);
    qsrand( mid.secsTo(QTime::currentTime()) );
    int randomNumber = 0;
    for(int i = 0; i < numOfFNodes; ++i)
    {
        randomNumber = (qrand() % randRange)+1; // ne zelimo kljuca ki je manjsi od ena
        this->Insert(randomNumber);
    }
}
