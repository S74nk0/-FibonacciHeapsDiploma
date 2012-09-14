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

//    if(argc == 2)
//    {
//        QString name = argv[1];
//        dij.loadGraph(name);
//        timer.start();
//        dij.doAlg();
//        qint64 elapsedTime_ms = timer.elapsed();
////        std::cout << "Time = " << elapsedTime_ms << " ms\n";
//        std::cout << elapsedTime_ms << "+";
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

////bundle
////1x
//#include "dijkstraalgorithmtemplate.h"
//#include <iostream>
////20
//#include <QtGui/QApplication>
//#include "mainwindow.h"
////30
//#include "benchmark.h"
////40
//#include "dijkstrawidget.h"

//typedef DijkstraAlgorithm<DFNode, Edge<DFNode> > DijkstraFib;
//typedef DijkstraAlgorithm<DNode, Edge<DNode> > DijkstraPriorityList;

//int main(int argc, char *argv[])
//{
//    // 1x
//    DijkstraFib dij;
//    DijkstraPriorityList prlist;
//    QElapsedTimer dijkstraTime;
//    qint64 elapsedTime = 0;
//    // 20
//    QApplication a(argc, argv);
//    MainWindow *w = 0;
//    // 30

//    //40
//    QApplication app(argc, argv);
//    app.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
//    DijkstraWidget *widget = 0;//new DijkstraWidget;
//    QMainWindow mainWindow;

//    if(argc == 3)
//    {
//        QString num = argv[1];
//        int option = num.toInt();
//        QString name = argv[2];
//        switch(option)
//        {
//            case 11:
//                dijkstraTime.start();
//                dij.loadGraph(name);
//                dij.doAlg();
//                elapsedTime = dijkstraTime.elapsed();
////                std::cout << "Time elapsed " << elapsedTime << " ms\n";
//                break;
//            case 12:
//                dijkstraTime.start();
//                prlist.loadGraph(name);
//                prlist.doAlg();
//                elapsedTime = dijkstraTime.elapsed();
////                std::cout << "Time elapsed " << elapsedTime << " ms\n";
//                break;
//            case 20:
//                w = new MainWindow;
//                w->show();
//                return a.exec();
//                break;
//            case 30:
//                break;
//            case 40:
//                widget = new DijkstraWidget;
//                mainWindow.setCentralWidget(widget);
//                mainWindow.show();
//                return app.exec();
//                break;
//            default:
//                //msg
//                break;
//        }
//    }
//    else
//    {
//        std::cout << "File name missing\n";
//    }

//    return 0;
//}
