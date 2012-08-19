#include "fibheapbenchmark.h"


FibHeapBenchmark::FibHeapBenchmark(int nodesAlloc) : FibHeapBase(), aloccSize(nodesAlloc), resetCount(0), upCount(0)
{
    array = new FNode*[aloccSize];
}
