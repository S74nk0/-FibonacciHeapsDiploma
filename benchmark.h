#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "fibheapbenchmark.h"
#include <QVector>
#include <QElapsedTimer>

class Benchmark
{
public:
    Benchmark();
    ~Benchmark();

    void worstCaseExtractMinTest(int nodes);
    void test();
    void worstCaseExtractMin(int nodes);

    void worstCaseExtractMinOutFiles(int nodes, int outFiles);

//private:
};

#endif // BENCHMARK_H
