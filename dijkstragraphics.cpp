#include "dijkstragraphics.h"
#include <QElapsedTimer>
#include <QMessageBox>

DijkstraGraphics::DijkstraGraphics() : DijkstraAlgorithm(), FibHeap(false), ElapsedTime(0)
{
}

DijkstraGraphics::~DijkstraGraphics()
{
    markedEdges.clear();
}

void DijkstraGraphics::addToScene(QGraphicsScene *scene)
{
    foreach(DijkstraGraphicsNode *node, this->Nodes) {
        scene->addItem(node);
    }
    foreach(DijkstraGraphicsEdge *edge, this->Edges) {
        scene->addItem(edge);
    }
}


void DijkstraGraphics::doAlg()
{
    if(this->Nodes.empty())
    {
        qDebug("Not initialized!");
        return;
    }

//    if(DijkstraGraphicsNode::searchEndNode == DijkstraGraphicsNode::searchStartNode
//            || !DijkstraGraphicsNode::searchEndNode
//            || !DijkstraGraphicsNode::searchStartNode) {
//        return;
//    }


    QElapsedTimer timer;

    if(this->FibHeap)
    {
        timer.start();
        doAlgFibHeaps();
        this->ElapsedTime = timer.nsecsElapsed();
    }
    else
    {
        timer.start();
        doAlgPriorityList();
        this->ElapsedTime = timer.nsecsElapsed();
    }

    QMessageBox msgBox;
    QString msg = "Times:\n";
    msg.append("Cas: " + QString::number(this->ElapsedTime) + "\n");
    msgBox.setText(msg);
    msgBox.exec();

}

void DijkstraGraphics::markRoute()
{
    DijkstraGraphicsNode *tmp = Nodes.first();//Nodes[0];
    DijkstraGraphicsNode *tmpPrev = 0;
    while(tmp)
    {
        tmp->routeNode = true;
        tmp->update();
        tmpPrev = static_cast<DijkstraGraphicsNode *>(tmp->prevScaned);

        for(int i=0; i < tmp->edges().count(); ++i) {
            if(tmp->edges().at(i)->startNode() == tmpPrev)
                markedEdges.push_back(
                            tmp->edges().at(i)
                            );
        }

        tmp = tmpPrev;
    }
}

void DijkstraGraphics::doAlgPriorityList()
{
    //start node, iz njega razvejemo drevo poti
    int sourceIndex = Nodes.count() - 1;//DijkstraGraphicsNode::searchStartNode->nodeId;
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;

    QList<DijkstraGraphicsNode *> S;
    QList<DijkstraGraphicsNode *> Q = Nodes.toList(); // prednostna vrsta, nisem cisto preprican ali je dejansko to prednostna vrsta ali

    if(sourceIndex != 0)
        Q.swap(0,sourceIndex);

    while(!Q.empty())
    {
        int sortEndIndex = 1;
        DijkstraGraphicsNode *u = Q.takeFirst(); // extract min
        S << u;

        u->state = SCANNED;

        DijkstraGraphicsNode *take = 0;
        for(int i=0; i<u->toEdges.size(); ++i)
        {

            if(u->toEdges[i]->endNode()->state != SCANNED)
            {
                int altDistance = u->key + u->toEdges[i]->getPrice();
                if(u->toEdges[i]->endNode()->state == UNLABELED)
                {
                    u->toEdges[i]->endNode()->state = LABELED;
                    u->toEdges[i]->endNode()->prevScaned = u;
                    u->toEdges[i]->endNode()->key = altDistance;
                    //fibheap insert Node
                }
                else if(altDistance < u->toEdges[i]->endNode()->key)
                {
                    u->toEdges[i]->endNode()->key = altDistance; // fib heap decrease key
                    u->toEdges[i]->endNode()->prevScaned = u;
                }

                take = Q.takeAt(Q.indexOf(u->toEdges[i]->endNode()));
                Q.push_front(take);
                ++sortEndIndex;
            }
        }
        qSort(Q.begin(), Q.begin()+sortEndIndex, keyLessThan<DijkstraGraphicsNode>); // sortira po vrsi
    }
}



void DijkstraGraphics::calculatePositions()
{
    int x = 0, y = 0;

    int nodeLineBreak = (int)sqrt(Nodes.count());

    if(nodeLineBreak > 70)
        y = -100;

    foreach (DijkstraGraphicsNode *node, Nodes) {

        node->moveBy(x*60, y*80);

        ++x;
        if(x == nodeLineBreak )
        {
            x = 0;
            ++y;
        }
    }
}

void DijkstraGraphics::hideUnmarked()
{
    foreach(DijkstraGraphicsNode *node, Nodes) {
        if(!node->routeNode)
        {
            foreach(GraphicsEdge<DijkstraGraphicsNode> *edge, node->edges())
                edge->hide();

            node->hide();
        }
        else
        {
            foreach(GraphicsEdge<DijkstraGraphicsNode> *edge, node->edges())
                if(!markedEdges.contains(edge))
                    edge->hide();
        }
    }
}

void DijkstraGraphics::doAlgFibHeaps()
{
    //start node, iz njega razvejemo drevo poti
    int sourceIndex = Nodes.size()-1;
    Nodes[sourceIndex]->key = 0;
    Nodes[sourceIndex]->state = LABELED;


    FibHeapDG heap;

    QList<DijkstraGraphicsNode *> S;
    heap.Insert(Nodes[sourceIndex]);

    while(heap.Min() != 0)
    {

        // velika pohitritev
        DijkstraGraphicsNode *u = heap.ExtractMin(); // extract min
        S << u;

        u->state = SCANNED;

        for(int i=0; i<u->toEdges.size(); ++i)
        {

            if(u->toEdges[i]->endNode()->state != SCANNED)
            {
                int altDistance = u->key + u->toEdges[i]->getPrice();
                if(u->toEdges[i]->endNode()->state == UNLABELED)
                {
                    u->toEdges[i]->endNode()->state = LABELED;
                    u->toEdges[i]->endNode()->prevScaned = u;
                    u->toEdges[i]->endNode()->key = altDistance;
                    heap.Insert(u->toEdges[i]->endNode());
                }
                else if(altDistance < u->toEdges[i]->endNode()->key)
                {
                    heap.DecreaseKey(u->toEdges[i]->endNode(), altDistance);
                    u->toEdges[i]->endNode()->prevScaned = u;
                }
            }
        }
    }

}
