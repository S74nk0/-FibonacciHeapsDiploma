#include "fibheapgraphics.h"
#include <QTimeLine>
#include <QGraphicsItemAnimation>

//FibHeapGraphics::FibHeapGraphics()
//{}

GraphicsFibNode *FibHeapGraphics::Insert(int key)
{
    GraphicsFibNode *tmpLast = this->LastNode;
    GraphicsFibNode *x = new GraphicsFibNode(key);
    x->referencePoint = this->referencePoint;
    FibHeapBase::Insert(x);//Insert(x);
    Nodes << x;
    if(n > 1) {
        Edges << new GraphicsFibEdge(tmpLast, x);
        this->LastNode->setPos(tmpLast->pos()); // for animation
    }
    return x;
}

GraphicsFibNode *FibHeapGraphics::ExtractMin(int fake)
{
    saveCurrentPositions();

    GraphicsFibNode *ret = FibHeapBase::ExtractMin(false);

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
    this->min->setStates();
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

//    LastNode->setPos(LastNode->x(),LastNode->y());
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
