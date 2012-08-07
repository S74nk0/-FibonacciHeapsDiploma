#ifndef FIBHEAPWIDGET_H
#define FIBHEAPWIDGET_H

class FibHeapWidget : public QGraphicsView
{
    Q_OBJECT

public:
    FibHeapWidget(QWidget *parent = 0);

    bool blockComponents();
    void nextStep();
    void insertNode(int key);
    void ExportHeap();

    void switchHeap();

    void extractMin();
    void decreaseKey(int key);
    void deleteNode();
    void clearSelected();
    void reset();

public slots:
    void zoomIn();
    void zoomOut();

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void scaleView(qreal scaleFactor);

private:
    void addNode(GraphicsFibNode *node);
    void updateMin();

//    GraphicsFibNode **selectedMin;
    FibHeapGraphics *selectedHeap;
    FibHeapGraphics *firstFibHeap;
    FibHeapGraphics *secondFibHeap;

    QPointF firstRefPoint;
    QPointF secondRefPoint;

    bool isDelete;
    bool isFirst;
};

#endif // FIBHEAPWIDGET_H