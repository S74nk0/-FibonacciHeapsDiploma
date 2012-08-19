#include "fibheapbenchmark.h"


FibHeapBenchmark::FibHeapBenchmark(int nodesAlloc) : FibHeapBase(), aloccSize(nodesAlloc), resetCount(0), upCount(0)
{
    array = new FNode*[aloccSize];
}

FibHeapBenchmark::~FibHeapBenchmark()
{
    for(int i=0; i<aloccSize; ++i)
    {
        delete array[i];
    }
    delete[] array;
}

void FibHeapBenchmark::GenerateWorsCase(int randRange) // using vector for the speed
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

void FibHeapBenchmark::ResetWorsCase(int randRange) // using vector for the speed
{
    this->n = 0;
    this->min = 0;
    this->LastNode = 0;

    ++resetCount;

    QTime mid(0,0,0);
    qsrand( mid.secsTo(QTime::currentTime()) );
    int numNodes = aloccSize-resetCount;
    for(int i = 0; i < numNodes; ++i)
    {
        array[i]->reset((qrand() % randRange)+1); // ne zelimo kljuca ki je manjsi od ena
        this->Insert(array[i]);
    }
}

bool FibHeapBenchmark::WorsCaseOneUp(int randRange)
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

bool FibHeapBenchmark::WorsCaseUp(int randRange)
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

void FibHeapBenchmark::initNodes()
{
    for(int i=0; i<aloccSize; ++i)
    {
        array[i] = new FNode(0);
    }
}

void FibHeapBenchmark::upCountReset()
{
    upCount = 0;
}
