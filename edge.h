#ifndef EDGE_H
#define EDGE_H

// Edge class template
template <class Node>
class Edge
{
public:
    Edge() : startN(0), endN(0), price(0) {}
    Edge(Node *startN, Node *endN) : startN(startN), endN(endN), price(-1) {}
    Edge(Node *startN, Node *endN, int price) : startN(startN), endN(endN), price(price)
    {
        startN->toEdges.push_back(this);
        endN->fromEdges.push_back(this);
    }

    Node *startNode() const {
        return startN;
    }
    Node *endNode() const {
        return endN;
    }
    int getPrice() const {
        return price;
    }

protected:
    Node *startN;
    Node *endN;

    int price;
};

#endif // EDGE_H
