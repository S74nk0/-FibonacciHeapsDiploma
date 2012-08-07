////#include "dijkstraalgorithmtemplate.h"
//#include "fibheapgraphics.h"

//int main(int argc, char *argv[])
//{
//    FibHeapGraphics heap;

//    (void)heap.ExtractMin();
//    heap.Delete(heap.Insert(5));

//////    DijkstraAlgorithm<DNode> dij;
////    DijkstraAlgorithm<DFNode> dij;
////    QString name = "scotland_big.txt";
//////    QString name = "primerGraf.txt";
////    QString fake = "sdddefefefefefe";
////    dij.loadGraph(name);

////    dij.doAlg();

//    return 0;
//}

//#include <QtGui>

//#include "graphwidget.h"

//int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

//    GraphWidget *widget = new GraphWidget;

//    QMainWindow mainWindow;
//    mainWindow.setCentralWidget(widget);
//    mainWindow.show();

//    return app.exec();
//}



////TEST BINARY
//#include "dijkstraalgorithmtemplate.h"

//int main(int argc, char *argv[])
//{
//    DijkstraAlgorithm<DFNode> dij;
//    QString name = "scotland_big.txt";
////    QString name = "primerGraf.txt";
//    QString fake = "sdddefefefefefe";
//    dij.loadGraph(name);

//    dij.doAlg();

//    return 0;
//}


//cel program z graficnim vmesnikom
#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
