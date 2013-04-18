////TEST BINARY
//#include "dijkstraalgorithmtemplate.h"
//#include <iostream>
//#include <QElapsedTimer>


//typedef DijkstraAlgorithm<DFNode, Edge<DFNode> > DijkstraFib;
//typedef DijkstraAlgorithm<DNode, Edge<DNode> > DijkstraPriorityList;

//int main(int argc, char *argv[])
//{
//    DijkstraFib dij;
////    DijkstraPriorityList dij;


//    QElapsedTimer timer;

////    if(argc == 2) // benchmarking
////    {
////        QString name = argv[1];
////        dij.loadGraph(name);
////        timer.start();
////        dij.doAlg();
////        qint64 elapsedTime_ms = timer.elapsed();
//////        std::cout << "Time = " << elapsedTime_ms << " ms\n";
////        std::cout << elapsedTime_ms << "+";
////    }
////    else
////    {
////        std::cout << "File name missing\n";
////    }

////    if(argc == 2)
////    {
////        QString name = argv[1];
////        dij.loadGraph(name);
////        std::cout << "Choose node index below " << dij.getNodeCount() << "\n";
////        int tmp = 0;
////        std::cin >> tmp;

////        dij.setIndex(tmp); // inf loop 2 no more
////        std::cout << "Processing " << tmp << "\n";
////        if(tmp >= dij.getNodeCount())
////        {
////            std::cout << "Index to large\n";
////            return 0;
////        }

////        timer.start();
////        dij.doAlg();
////        qint64 elapsedTime_ms = timer.elapsed();
////        std::cout << "Time = " << elapsedTime_ms << " ms\n";
////        dij.printResaults();
////    }
////    else
////    {
////        std::cout << "File name missing\n";
////    }

//    if(argc == 3)
//    {
//        QString name = argv[1];
//        QString num = argv[2];
//        dij.loadGraph(name);
//        std::cout << "Choose node index below " << dij.getNodeCount() << "\n";
//        int tmp = num.toInt();
////        std::cin >> tmp;

//        dij.setIndex(tmp); // inf loop 2 no more
//        std::cout << "Processing " << tmp << "\n";
//        if(tmp >= dij.getNodeCount())
//        {
//            std::cout << "Index to large\n";
//            return 0;
//        }

//        timer.start();
//        dij.doAlg();
//        qint64 elapsedTime_ms = timer.elapsed();
//        std::cout << "Time = " << elapsedTime_ms << " ms\n";
//        dij.printResaults();
//    }
//    else
//    {
//        std::cout << "File name and index missing\n";
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

