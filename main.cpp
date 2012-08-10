////TEST BINARY
//#include "dijkstraalgorithmtemplate.h"

//int main(int argc, char *argv[])
//{
//    DijkstraAlgorithm<DFNode, Edge<DFNode> > dij;
//    QString name = "scotland_big.txt";
////    QString name = "primerGraf.txt";
//    QString fake = "sdddefefefefefe";
//    dij.loadGraph(name);

//    dij.doAlg();

//    return 0;
//}


////cel program z graficnim vmesnikom
//#include <QtGui/QApplication>
//#include "mainwindow.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}

////TEST TIMES

//#include "benchmark.h"

//int main(int argc, char *argv[])
//{

//    Benchmark bench;

////    bench.worstCaseExtractMin(10000);
////    bench.worstCaseExtractMinTest(10000000);

////    bench.worstCaseExtractMinOutFiles(50000000, 30); // to bo miki generiral podatke



//    return 0;
//}

////DijkstraGraphics
#include <QtGui>

//#include "dijkstragraphics.h"

#include "dijkstrawidget.h"

int main(int argc, char **argv)
{

//    DijkstraGraphics dij;

//    QString name = "scotland_big.txt";
//    QString fake = "sdddefefefefefe";
//    dij.loadGraph(name);
//    dij.loadGraph(fake);

    QApplication app(argc, argv);
    DijkstraWidget *widget = new DijkstraWidget;

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(widget);

    mainWindow.show();
    return app.exec();

}

