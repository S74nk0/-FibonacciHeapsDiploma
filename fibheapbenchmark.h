#ifndef FIBHEAPBENCHMARK_H
#define FIBHEAPBENCHMARK_H

#include "fibnodebasetemplate.h"
#include "fibheapbasetemplate.h"

class FNode : public FibNodeBase<FNode>
{
public:
    FNode(int k) : FibNodeBase(k)
    {}

    void reset(int k)
    {
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
    FibHeapBenchmark(int nodesAlloc) : FibHeapBase(), aloccSize(nodesAlloc), resetCount(0), upCount(0)
    {
        array = new FNode*[aloccSize];
    }

    ~FibHeapBenchmark()
    {
        for(int i=0; i<aloccSize; ++i)
        {
            delete array[i];
        }
        delete[] array;
    }

    //the function generates the nodes and the first extract min call is the worst case because the nodes are all in one line like in a list
    void GenerateWorsCase(int randRange = RAND_MAX) // using vector for the speed
    {
        QTime mid(0,0,0);
        qsrand( mid.secsTo(QTime::currentTime()) );
        int randomNumber = 0;
        for(int i = 0; i < aloccSize; ++i)
        {
            randomNumber = (qrand() % randRange)+1; // ne zelimo kljuca ki je manjsi od ena
            array[i] = this->Insert(randomNumber);//new FNode(randomNumber);//this->Insert(randomNumber);
        }
    }

    //the function generates the nodes and the first extract min call is the worst case because the nodes are all in one line like in a list
    void ResetWorsCase(int randRange = RAND_MAX) // using vector for the speed
    {
        this->n = 0;
        this->min = 0;
        this->LastNode = 0;

        ++resetCount;

        QTime mid(0,0,0);
        qsrand( mid.secsTo(QTime::currentTime()) );
//        int randomNumber = 0;
        int numNodes = aloccSize-resetCount;
        for(int i = 0; i < numNodes; ++i)
        {
            array[i]->reset((qrand() % randRange)+1); // ne zelimo kljuca ki je manjsi od ena
            this->Insert(array[i]);
        }
    }

    bool WorsCaseOneUp(int randRange = RAND_MAX)
    {
        if(aloccSize < upCount)
            return false; // the bechmarking is finished

        this->n = 0;
        this->min = 0;
        this->LastNode = 0;

        QTime mid(0,0,0);
        qsrand( mid.secsTo(QTime::currentTime()) );
        for(int i = 0; i < upCount; ++i)
        {
            array[i]->reset((qrand() % randRange)+1); // ne zelimo kljuca ki je manjsi od ena
            this->Insert(array[i]);
        }

        array[upCount++] = this->Insert( (qrand() % randRange)+1 );

        return true;
    }

    bool WorsCaseUp(int randRange = RAND_MAX)
    {
        if(aloccSize == upCount)
            return false; // the bechmarking is finished

        this->n = 0;
        this->min = 0;
        this->LastNode = 0;

        ++upCount;

        QTime mid(0,0,0);
        qsrand( mid.secsTo(QTime::currentTime()) );
        for(int i = 0; i < upCount; ++i)
        {
            array[i]->reset((qrand() % randRange)+1); // ne zelimo kljuca ki je manjsi od ena
            this->Insert(array[i]);
        }

        return true;
    }

    void initNodes()
    {
        for(int i=0; i<aloccSize; ++i)
        {
            array[i] = new FNode(0);
        }
    }

    void upCountReset()
    {
        upCount = 0;
    }

private:
    FNode **array;
    int aloccSize;
    int resetCount;
    int upCount;
};

#endif // FIBHEAPBENCHMARK_H
