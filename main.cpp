////TEST BINARY
//#include "dijkstraalgorithmtemplate.h"
//#include <iostream>

//typedef DijkstraAlgorithm<DFNode, Edge<DFNode> > DijkstraFib;
//typedef DijkstraAlgorithm<DNode, Edge<DNode> > DijkstraPriorityList;

//int main(int argc, char *argv[])
//{
//    DijkstraFib dij;
////    DijkstraPriorityList dij;

//    if(argc == 2)
//    {
//        QString name = argv[1];
//        dij.loadGraph(name);
//        dij.doAlg();
//    }
//    else
//    {
//        std::cout << "File name missing\n";
//    }

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

//////DijkstraGraphics
//#include <QtGui>

//#include "dijkstrawidget.h"

//int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);
//    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

//    DijkstraWidget *widget = new DijkstraWidget;

//    QMainWindow mainWindow;
//    mainWindow.setCentralWidget(widget);

//    mainWindow.show();
//    return app.exec();
//}

