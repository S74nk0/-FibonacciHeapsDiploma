#ifndef FIBHEAPBENCHMARK_H
#define FIBHEAPBENCHMARK_H

#include "fibnodebasetemplate.h"
#include "fibheapbasetemplate.h"

class FNode : public FibNodeBase<FNode>
{
public:
    FNode(int k) : FibNodeBase(k)
    {}

    void reset(int k) {
        this->Child = 0;
        this->Prev = this;
        this->Next = this;
        this->Parent = 0;
        this->key = k;
        this->degree = 0;
        this->mark = false;
    }

    //dummdy functions to satisfy the template (there is probably a better way but this is for now the easiest way and with no pefrormance penaulty (extremaley small if any, probabley none))
    inline void setStates() const {}
    inline void update() const {}
};

class FibHeapBenchmark : public FibHeapBase<FNode>
{
public:
    FibHeapBenchmark(int nodesAlloc);
    ~FibHeapBenchmark();

    //the function generates the nodes and the first extract min call is the worst case because the nodes are all in one line like in a list
    void GenerateWorsCase(int randRange = RAND_MAX);

    void ResetWorsCase(int randRange = RAND_MAX);
    bool WorsCaseOneUp(int randRange = RAND_MAX);
    bool WorsCaseUp(int randRange = RAND_MAX);
    void initNodes();
    void upCountReset();

private:
    FNode **array;
    int aloccSize;
    int resetCount;
    int upCount;
};

#endif // FIBHEAPBENCHMARK_H
