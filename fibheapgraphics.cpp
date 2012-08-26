#include "fibheapgraphics.h"
#include <QTimeLine>
#include <QGraphicsItemAnimation>



FibHeapGraphics::FibHeapGraphics() : FibHeapBase(), decreaseKeyTempNode(0)
{}

FibHeapGraphics::~FibHeapGraphics()
{
    Nodes.clear();
    Edges.clear();
}

GraphicsFibNode *FibHeapGraphics::Insert(int key)
{
    GraphicsFibNode *tmpLast = this->LastNode;
    GraphicsFibNode *x = new GraphicsFibNode(key);
    x->referencePoint = this->referencePoint;
    if(Nodes.isEmpty())
        x->setPos(this->referencePoint);

    FibHeapBase::Insert(x);//Insert(x);
    Nodes << x;
    if(n > 1) {
        Edges << new GraphicsFibEdge(tmpLast, x);
        this->LastNode->setPos(tmpLast->pos()); // for animation
    }
    return x;
}

GraphicsFibNode *FibHeapGraphics::ExtractMin(bool deleteFunc /*= false*/)
{
    saveCurrentPositions();

    GraphicsFibNode *ret = FibHeapBase::ExtractMin(deleteFunc);

    //Update the lists
    if(!Nodes.removeOne(ret) && !Nodes.isEmpty())
        qDebug("Nodes remove error");
    this->unlinkEdges();
    if(!Edges.isEmpty())
    {
        delete Edges.last();
        Edges.pop_back();
    }
    this->linkEdges();

    setFirstPositions(); // set first
    animate(100);

    return ret;
}

void FibHeapGraphics::unlinkEdges()
{
    foreach(GraphicsFibEdge *edge, Edges)
    {
        if(!edge->unlink())
            qDebug("FibHeapGraphics::unlinkEdges -> unlink error!");
    }
}

void FibHeapGraphics::linkEdges()
{
    int edgeIndex = 0;
    foreach(GraphicsFibNode *node, Nodes)
    {
        if(node->Parent != 0)
            Edges[edgeIndex++]->setNodes(node->parent(), node);
    }

    GraphicsFibNode *start = 0;
    if(this->LastNode)
        start = this->LastNode->next();

    while (start != this->LastNode) {
        Edges[edgeIndex++]->setNodes(start, start->next() );
        start = start->next();
    }
}

void FibHeapGraphics::setStates()
{
    this->LastNode->next()->setStates();
}

void FibHeapGraphics::updateEdges()
{
    this->unlinkEdges();
    this->linkEdges();
}

void FibHeapGraphics::animate(int timemil)
{
    if(Nodes.isEmpty())
        return;
    if(Nodes.first()->positions.isEmpty())
        return;
    if(Nodes.first()->positions.count() == 1)
    {
        foreach(GraphicsFibNode *node, Nodes) {
            node->positions.pop_front();
        }
        return;
    }

    QTimeLine *timeline = new QTimeLine;
    timeline->setDuration (timemil);
    timeline->setCurveShape (QTimeLine::EaseInOutCurve); // OK = EaseOutCurve
    QObject::connect (timeline, SIGNAL(finished()), timeline, SLOT(deleteLater()));

    for(int i = 0; i < Nodes.size(); ++i)
    {
        Nodes.value(i)->positions.pop_front();
        QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
        animation->setItem(Nodes.value(i));
        animation->setTimeLine(timeline);
        animation->setPosAt(1.0, Nodes.value(i)->positions[0]);
        QObject::connect (timeline, SIGNAL(finished()), animation, SLOT(deleteLater()));
    }


//    //kaj je to sm pozabu ze poglej pa se spomni
//    QPointF cent = this->min->pos();
//    this->translate(cent.x(), cent.y());

    timeline->start();
}

void FibHeapGraphics::setFirstPositions()
{
    if(!Nodes.isEmpty())
        if(Nodes.first()->positions.isEmpty())
            return;

    foreach (GraphicsFibNode *node, Nodes)
    {
        node->setPos(node->positions.first() );
    }
}

void FibHeapGraphics::animateInsert()
{
    QTimeLine *timeline = new QTimeLine;
    timeline->setDuration (300);
    timeline->setCurveShape (QTimeLine::EaseInOutCurve); // OK = EaseOutCurve
    QObject::connect (timeline, SIGNAL(finished()), timeline, SLOT(deleteLater()));

    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
    animation->setItem(LastNode);
    animation->setTimeLine(timeline);
    animation->setPosAt(1.0, QPointF(LastNode->x()+50,LastNode->y()));
    QObject::connect (timeline, SIGNAL(finished()), animation, SLOT(deleteLater()));

    timeline->start();
}

void FibHeapGraphics::saveCurrentPositions()
{
    foreach (GraphicsFibNode *node, Nodes) {
        node->positions << node->pos();
    }
}

bool FibHeapGraphics::blockComponents()
{
    if(!Nodes.isEmpty())
        if(!Nodes.first()->positions.isEmpty())
            return true;

    return false;
}

bool FibHeapGraphics::oneStatesLeft()
{
    if(!Nodes.isEmpty())
        if(Nodes.first()->positions.count() == 1)
            return true;

    return false;
}

void FibHeapGraphics::clearPositions()
{
    foreach (GraphicsFibNode *node, Nodes) {
        node->positions.clear();
    }
}


void FibHeapGraphics::clear()
{
    while(!Edges.isEmpty())
    {
        delete Edges.first();
        Edges.pop_front();
        delete Nodes.first();
        Nodes.pop_front();
    }
    while(!Nodes.isEmpty())
    {
        delete Nodes.first();
        Nodes.pop_front();
    }

    this->min = this->LastNode = 0;
    this->n = 0;
}

FibHeapGraphics *FibHeapGraphics::Union(FibHeapGraphics *H2)
{
    FibHeapGraphics *newHeapUnion = static_cast<FibHeapGraphics *>(
                FibHeapBase::Union(H2)
                                                               );
    FibHeapGraphics *newHeap = new FibHeapGraphics();
    newHeap->min = newHeapUnion->min;
    newHeap->n = newHeapUnion->n;
    newHeap->LastNode = newHeapUnion->LastNode;

    newHeap->referencePoint = this->referencePoint;

    foreach(GraphicsFibNode *node, H2->Nodes) {
        node->referencePoint = this->referencePoint;
    }

    newHeap->Nodes = this->Nodes
            << H2->Nodes;
    newHeap->Edges << this->Edges
                   << H2->Edges
                   << new GraphicsFibEdge(this->LastNode, H2->LastNode->next());

    newHeap->saveCurrentPositions();
    newHeap->setStates();
    newHeap->updateEdges();
    newHeap->setFirstPositions();

    return newHeap;
}

void FibHeapGraphics::DecreaseKey(GraphicsFibNode *x, int k)
{
    this->saveCurrentPositions();

    GraphicsFibNode *tmpParent = 0;
    if(this->decreaseKeyTempNode)
    {
        tmpParent = this->decreaseKeyTempNode->parent();
        this->Cut(this->decreaseKeyTempNode);

        if(tmpParent)
        {
            this->CascadingCut(tmpParent);
        }
    }
    else
    {
        this->DecreaseKeyGraphics(x,k);
        this->setStates();
    }

    this->updateEdges();
    this->setFirstPositions(); // set first
    this->animate(300);
}

QList<GraphicsFibEdge *> FibHeapGraphics::edges() const
{
    return this->Edges;
}

QList<GraphicsFibNode *> FibHeapGraphics::nodes() const
{
    return this->Nodes;
}

void FibHeapGraphics::ImportHeap(QString &fileName, QGraphicsScene *scene)
{
    FibHeapBase::ImportHeap(fileName);

    importNodes(this->min, scene);
    linkEdgesNew(scene);
    setStates();
    clearPositions();
}

void FibHeapGraphics::importNodes(GraphicsFibNode *node, QGraphicsScene *scene)
{
    if(!node)
        return;

    GraphicsFibNode *nodeTmp = node;
    do
    {
        nodeTmp->referencePoint = this->referencePoint;
        Nodes << nodeTmp;
        scene->addItem(nodeTmp);
        importNodes(nodeTmp->child(), scene);
        nodeTmp = nodeTmp->next();
    } while(nodeTmp != node);
}

void FibHeapGraphics::linkEdgesNew(QGraphicsScene *scene)
{
    foreach(GraphicsFibNode *node, Nodes)
    {
        if(node->Parent != 0)
        {
            Edges << new GraphicsFibEdge(node->parent(), node);
            scene->addItem(Edges.last());
        }
    }

    GraphicsFibNode *start = 0;
    if(this->LastNode)
        start = this->LastNode->next();

    while (start != this->LastNode) {
        Edges << new GraphicsFibEdge(start, start->next() );
        scene->addItem(Edges.last());
        start = start->next();
    }
}

void FibHeapGraphics::DecreaseKeyGraphics(GraphicsFibNode *x, int k)
{
    if(k > x->key)
    {
        return;
    }

    x->key = k;
    x->update(); // for the graphics/visuals nothing to do with the algorithm

    GraphicsFibNode *y = x->parent();

    if(y != 0 && x->key < y->key)
    {
        this->Cut(x); //base function
        this->CascadingCut(y);
    }

    if(x->key < this->min->key)
    {
        this->min = x;
    }
}

void FibHeapGraphics::Cut(GraphicsFibNode *x)
{
    FibHeapBase::Cut(x);

    //graphics functions
    x->update(); // for the graphics/visuals nothing to do with the algorithm
    this->LastNode->next()->setStates(); // for the graphics/visuals nothing to do with the algorithm
}

void FibHeapGraphics::CascadingCut(GraphicsFibNode *y)
{
    GraphicsFibNode *z = y->parent();
    if(z != 0)
    {
        if(y->mark == false)
        {
            y->mark = true;
            y->update(); // for the graphics/visuals nothing to do with the algorithm
        }
        else
        {
            this->decreaseKeyTempNode = y;
            return;
        }
    }
    this->decreaseKeyTempNode = 0;
}

bool FibHeapGraphics::decreaseKeyTmpNode() const
{
    return this->decreaseKeyTempNode;
}

////19.2
//void FibHeapGraphics::Consolidate()
//{
//    double f = log( static_cast<double>(this->n) )/ln;
//    int D = qRound(f) + 1/*2*/;//D();

//    GraphicsFibNode **A = new GraphicsFibNode*[D];

//    for(int i = 0; i < D; ++i)
//    {
//        A[i] = 0;
//    }

//    GraphicsFibNode *x = 0, *y = 0, *tmp = 0;

//    x = this->min;
//    do
//    {
//        int d = x->degree;

//        while(A[d] != 0 && x != A[d])
//        {
//            y = A[d];
//            if(x != 0 && y != 0)
//            {
//                if(x->key > y->key)
//                {
//                    tmp = x;
//                    x = y;
//                    y = tmp;
//                }
//                if(y == this->min)
//                    this->min = x;

//                this->Link(y, x);// states change
//            }

//            A[d] = 0;
//            ++d;
//        }
//        A[d] = x;

//        x = x->next();
//    }while(x != this->min);


//    for(int i = 0; i < D; ++i)
//    {
//        if(A[i] != 0)
//        {
//            if(A[i]->key < this->min->key || (this->min->key == A[i]->key && A[i]->degree < this->min->degree)) // speed up if we set the min node as also th node with the min degree
//            {
//                this->min = A[i];
//            }
//        }
//    }

//    delete[] A;
//}

//void FibHeapGraphics::Link(GraphicsFibNode *y, GraphicsFibNode *x)
//{
//    FibHeapBase::Link(y,x);
//    //the update fuction is only for the visuals/ graphics and has nothing to do with the algorithm
//    y->update(); //
//    this->LastNode->next()->setStates(); // again this part is only for the graphical representation and not esential to the algorithm it has no part in the pseudocode in the alghorithm
//}

//GraphicsFibNode *FibHeapGraphics::ExtractMinPrivate(bool deleteFunc/* = false*/)
//{
//    GraphicsFibNode *z = this->min;

//    if(z != 0)
//    {
//        GraphicsFibNode *ChildListEnd = 0;
//        if(z->Child != 0)
//        {
//            GraphicsFibNode *ChildListStart = z->child();
//            for(int i = 0; i < z->degree; ++i)
//            {
//                ChildListStart->Parent = 0;
//                ChildListStart = ChildListStart->next();
//            }

//            ChildListEnd = ChildListStart->prev();

//            GraphicsFibNode *FirstNode = this->LastNode->next();

//            ChildListStart->Prev = this->LastNode;
//            this->LastNode->Next = ChildListStart;

//            ChildListEnd->Next = FirstNode;
//            FirstNode->Prev = ChildListEnd;

//            this->LastNode = ChildListEnd;
//        }

//        if(z->unlink())
//        {
//            this->min = 0;
//            this->LastNode = 0;
//        }
//        else
//        {
//            //ce je z = LastNode
//            if(z == LastNode)
//                LastNode = z->prev();

//            this->min = z->next();
//            if(this->min->Child != 0 && !deleteFunc && ChildListEnd != 0) // za strukturo (obliko fibHeapa, ni bistveno za kopico sam zgradi jo po moji volji -> lepsa je)
//            {
//                this->min = ChildListEnd;
//            }

//            //this part of the code isn't for the alghorithm but for the template to satisfy one function for both graphical node and non graphical
//            this->LastNode->next()->setStates(); // the setStates
//            //end of template function

//            this->Consolidate();
//        }
//        --this->n;
//    }

//    return z;
//}
