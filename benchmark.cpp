#include "benchmark.h"
#include <limits>

#include <iostream>
#include <QFile>
#include <QString>
#include <QTextStream>

Benchmark::Benchmark()
{}

Benchmark::~Benchmark()
{
}

void Benchmark::worstCaseExtractMinTest(int nodes)
{
    FibHeapBenchmark *heap = new FibHeapBenchmark(nodes); // 10000000 = OK, 50000000 = too high
    heap->GenerateWorsCase();
    QElapsedTimer time;
    time.start();
    heap->ExtractMin();
//    std::cout << nodes << ": " << time.elapsed() << " ms" << std::endl;
    std::cout << nodes << ": " << time.nsecsElapsed() << " ns" << std::endl;
    delete heap;
}

void Benchmark::test()
{
    QElapsedTimer time;
    FibHeapBenchmark *heap = new FibHeapBenchmark(10000000); // 10000000 = OK, 50000000 = too high
    heap->GenerateWorsCase(); // 10000000
    time.start();
    heap->ExtractMin();
    std::cout << 10000000 << ": " << time.elapsed() << " ms" << std::endl;


    heap->ResetWorsCase(); //9999999
    time.restart();
    time.start();
    heap->ExtractMin();
    std::cout << 9999999 << ": " << time.elapsed() << " ms" << std::endl;

    heap->ResetWorsCase(); //9999998
    time.restart();
    time.start();
    heap->ExtractMin();
    std::cout << 9999998 << ": " << time.elapsed() << " ms" << std::endl;

    heap->ResetWorsCase(); //9999997
    time.restart();
    time.start();
    heap->ExtractMin();
    std::cout << 9999997 << ": " << time.elapsed() << " ms" << std::endl;

    delete heap;
}

void Benchmark::worstCaseExtractMin(int nodes)
{
    FibHeapBenchmark *heap = new FibHeapBenchmark(nodes); // 10000000 = OK, 50000000 = too high

    int i = 0;
    qint64 timeElapsed;
    while(heap->WorsCaseOneUp())
    {
        QElapsedTimer time;
        time.start();
        heap->ExtractMin();
        timeElapsed = time.nsecsElapsed();
        std::cout << ++i << ":\t"
                  <<  timeElapsed
                  << " ns\t"
                  << (int)(timeElapsed/1000000)
                  << " ms\t"
                  << std::endl;
    }

    delete heap;
}

void Benchmark::worstCaseExtractMinOutFiles(int nodes, int outFiles)
{
    FibHeapBenchmark *heap = new FibHeapBenchmark(nodes); // 10000000 = OK, 50000000 = too high
    heap->initNodes(); // we do this only once

    for(int fileIndex = 0; fileIndex < outFiles; ++fileIndex)
    {
        QString FileName = "wcExMinResaults" + QString::number(fileIndex);
        QFile datoteka(FileName);
        datoteka.open(QIODevice::WriteOnly);
        QTextStream out(&datoteka);

        heap->upCountReset(); // set the upCount to 0
        int i = 0;
        qint64 timeElapsed;
        while(heap->WorsCaseUp())
        {
            QElapsedTimer time;
            time.start();
            heap->ExtractMin();
            timeElapsed = time.nsecsElapsed();
            out << i++ << ":\t"
                      <<  timeElapsed
                      << " ns\t"
                      << (int)(timeElapsed/1000000)
                      << " ms\t"
                      << "\n";
        }

        datoteka.close();
    }

    delete heap;
}
