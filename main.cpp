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
