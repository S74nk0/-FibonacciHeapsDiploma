#include "graphicsfibnode.h"

//static members
GraphicsFibNode *GraphicsFibNode::minfNode = 0;
GraphicsFibNode *GraphicsFibNode::minfNode2 = 0;
GraphicsFibNode *GraphicsFibNode::selected = 0;



GraphicsFibNode::GraphicsFibNode() : GraphicsNode(), FibNodeBase()
{}

GraphicsFibNode::GraphicsFibNode(int k) : GraphicsNode(), FibNodeBase(k)
{}

GraphicsFibNode::GraphicsFibNode(int k, int d, bool m) : GraphicsNode(), FibNodeBase(k,d,m)
{}

GraphicsFibNode::~GraphicsFibNode()
{
    if(this->selected == this)
    {
        this->selected = 0;
    }
}

void GraphicsFibNode::makeChildLink(GraphicsFibNode *child)
{
    FibNodeBase::makeChildLink(child);
    if(this->Child->degree < child->degree)
        this->Child = child;
}

void GraphicsFibNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken || this == this->selected) {
        gradient.setColorAt(0, Qt::blue);
    }
    else {
        if(this->mark)
            gradient.setColorAt(0, Qt::darkYellow);
        else if(this == this->minfNode || this == this->minfNode2)
            gradient.setColorAt(0, Qt::red);
        else
            gradient.setColorAt(0, Qt::yellow);

    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);

    QString num = QString::number(this->key);
    painter->drawText(-5*num.size(),5, num);//painter->drawText(-5,5, QString::number(fNode->key));
}

void GraphicsFibNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    GraphicsFibNode *tmpNode = this->selected;
    this->selected = this;
    if(tmpNode != 0) // tu se pojavlja problem sigsegv, najverjetneje kaze an zbrisano lokacijo
        tmpNode->update();
    newPos = this->pos();
    update();
    QGraphicsItem::mousePressEvent(event);
}

void GraphicsFibNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setPos(newPos);
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void GraphicsFibNode::setStates()
{
    GraphicsFibNode *first = this;
    GraphicsFibNode *tmp = first->prev();

    tmp->setPos(referencePoint); // 0 , 0
//    tmp->positions << tmp->pos();

    GraphicsFibNode * fNode;
    GraphicsFibNode * sNode;
    float offset = 1;

    do
    {
        fNode = tmp;
        sNode = tmp->prev();
        offset = (float)getOffset(tmp/*, true*/)/*+2*/;//tmp->degree;
        if(offset <= 4)
            offset += 6;
        offset = offset*((5*offset+offset)/(offset*0.7));

        sNode->setPos(fNode->x()-offset/*(50*offset)*1.3*/, fNode->y());
//        sNode->positions << sNode->pos();

        formTree(tmp->child());
        tmp = tmp->prev();
    } while (tmp != first);
    formTree(tmp->child());

    //save states positions
    savePositions(this); // otherwise the positions are screwed
}

void GraphicsFibNode::formTree(GraphicsFibNode * node)
{
    if(!node)
        return;

    GraphicsFibNode *tmp = node->prev();

    GraphicsFibNode *pNode = node->parent();
    tmp->setPos(pNode->x(), pNode->y()+50);
//    tmp->positions << tmp->pos();

    GraphicsFibNode * fNode;
    GraphicsFibNode * sNode;
    float offset = 1;

//    int y = tmp->node->y();
    while(tmp != node)
    {
        fNode = tmp;
        sNode = tmp->prev();
        offset = (float)getOffset(tmp/*, true*/)/*+2*/;// * (int)(100/(tmp->degree+1));
        if(offset <= 4)
            offset += 5;
        offset = offset*((5*offset+offset)/(offset*0.7));

        sNode->setPos(fNode->x()-offset/*(50*offset)*/, /*y+(50*offset)*/ fNode->y());
//        sNode->positions << sNode->pos();

        formTree(tmp->child());
        tmp = tmp->prev();
    }
    formTree(tmp->child());
}

int GraphicsFibNode::getOffset(GraphicsFibNode *node)
{
    int off = node->degree+1;
    GraphicsFibNode *child = node->child();
    if(child == 0)
        return off;
    do {
        off++;
        off += getOffset(child);
        child = child->next();
    } while (child != node->child());
    return off;
}

void GraphicsFibNode::savePositions(GraphicsFibNode *node)
{
    if(!node)
        return;

    GraphicsFibNode *nodeSet = node;
    do
    {
        nodeSet->positions << nodeSet->pos();
        savePositions(nodeSet->child());
        nodeSet = nodeSet->next();
    } while(nodeSet != node);
}
