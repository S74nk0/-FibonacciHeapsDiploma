#ifndef FIBHEAPGRAPHICS_H
#define FIBHEAPGRAPHICS_H

#include "fibheapbasetemplate.h"
#include "graphicsfibnode.h"
#include "graphicsfibedge.h"

class FibHeapGraphics : public FibHeapBase<GraphicsFibNode>
{
public:
    FibHeapGraphics();
    ~FibHeapGraphics();
    GraphicsFibNode *Insert(int key);
    GraphicsFibNode *ExtractMin(bool deleteFunc = false);
    FibHeapGraphics *Union(FibHeapGraphics *H2);
    void DecreaseKey(GraphicsFibNode *x, int k);
    void ImportHeap(QString &fileName, QGraphicsScene *scene);



    void setStates();
    void clear();

    void animate(int timemil);
    void animateInsert();
    void setFirstPositions();
    void saveCurrentPositions();
    void clearPositions();

    bool blockComponents();
    bool oneStatesLeft();
    bool decreaseKeyTmpNode() const;

    QPointF referencePoint;

    QList<GraphicsFibEdge *> edges() const;
    QList<GraphicsFibNode *> nodes() const;

private:
    QList<GraphicsFibEdge *> Edges;
    QList<GraphicsFibNode *> Nodes;
    void importNodes(GraphicsFibNode *node, QGraphicsScene *scene);
    void unlinkEdges();
    void linkEdges();
    void linkEdgesNew(QGraphicsScene *scene);
    void updateEdges();

    //decrease key graphics
    void DecreaseKeyGraphics(GraphicsFibNode *x, int k);
    GraphicsFibNode *decreaseKeyTempNode;


    //19.2
//    void Link(GraphicsFibNode *y, GraphicsFibNode *x);

    //19.3
    void Cut(GraphicsFibNode *x);
    void CascadingCut(GraphicsFibNode *y);

};

#endif // FIBHEAPGRAPHICS_H
