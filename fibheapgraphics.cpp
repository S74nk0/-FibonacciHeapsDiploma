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

void FibHeapGraphics::Insert(int key, QGraphicsScene *scene)
{
    GraphicsFibEdge *tmpEdge = 0;
    GraphicsFibNode *x = new GraphicsFibNode(key);
    x->referencePoint = this->referencePoint;
    if(Nodes.isEmpty())
        x->setPos(this->referencePoint);

    FibHeapBase::Insert(x);//Insert(x);
    Nodes << x;
    scene->addItem(x);
    if(n > 1) {
//        Edges << new GraphicsFibEdge(tmpLast, x);
//        this->LastNode->setPos(tmpLast->pos()); // for animation
        tmpEdge = new GraphicsFibEdge(min, x);
        Edges << tmpEdge;
        x->setPos(min->x(),min->y()+2);
        scene->addItem(tmpEdge);
    }
//    saveCurrentPositions(); // error
    this->unlinkEdges();
    setStates();
    this->linkEdges();
    setFirstPositions(); // set first
    animate(300);

}

GraphicsFibNode *FibHeapGraphics::ExtractMin()
{
    saveCurrentPositions();

    GraphicsFibNode *ret = FibHeapBase::ExtractMin();

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

    GraphicsFibNode *start = this->rootList.getFirst();
    GraphicsFibNode *end = this->rootList.getLast();

    while (start != end) {
        Edges[edgeIndex++]->setNodes(start, start->next() );
        start = start->next();
    }
}

void FibHeapGraphics::setStates()
{
    this->rootList.getFirst()->setStates();
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


//    //centriranje tocke na min
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

//void FibHeapGraphics::animateInsert()
//{
//    QTimeLine *timeline = new QTimeLine;
//    timeline->setDuration (300);
//    timeline->setCurveShape (QTimeLine::EaseInOutCurve); // OK = EaseOutCurve
//    QObject::connect (timeline, SIGNAL(finished()), timeline, SLOT(deleteLater()));

//    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
//    animation->setItem(LastNode);
//    animation->setTimeLine(timeline);
//    animation->setPosAt(1.0, QPointF(LastNode->x()+50,LastNode->y()));
//    QObject::connect (timeline, SIGNAL(finished()), animation, SLOT(deleteLater()));

//    timeline->start();
//}

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

    this->min = 0;
    this->rootList.setEmpty();
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
//    newHeap->LastNode = newHeapUnion->LastNode;
    newHeap->rootList.setFirst(newHeapUnion->rootList.getFirst());

    newHeap->referencePoint = this->referencePoint;

    foreach(GraphicsFibNode *node, H2->Nodes) {
        node->referencePoint = this->referencePoint;
    }

    newHeap->Nodes = this->Nodes
            << H2->Nodes;
    newHeap->Edges << this->Edges
                   << H2->Edges
//                      << new GraphicsFibEdge(this->LastNode, H2->LastNode->next());
                   << new GraphicsFibEdge(this->rootList.getLast(), H2->rootList.getFirst());

    newHeap->saveCurrentPositions();
    newHeap->setStates();
    newHeap->updateEdges();
    newHeap->setFirstPositions();

    return newHeap;
}

void FibHeapGraphics::DecreaseKey(GraphicsFibNode *x, int k)
{
    if(!Nodes.contains(x)) // check if node is part of current heap
    {
        x->update();
        return;
    }

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

    GraphicsFibNode *start = this->rootList.getFirst();
    GraphicsFibNode *end = this->rootList.getLast();
//    if(this->LastNode)
//        start = this->LastNode->next();

    while (start != end/*this->LastNode*/) {
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
//    this->LastNode->next()->setStates(); // for the graphics/visuals nothing to do with the algorithm
    this->setStates();
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

