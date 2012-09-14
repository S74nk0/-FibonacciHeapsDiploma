#ifndef CDLIST_H
#define CDLIST_H

template<class Node> // node needs to have the fibnodebase, base template 
class CDList // circular doubley list
{
public:
    CDList() : first(0) {
    }

    void setFirst(Node *newFirst) {
        first = newFirst;
    }

    inline void setEmpty() {
        first = 0;
    }

    inline void removeUpdate(Node *remove) {
        if(remove == first && first != first->prev())
            first = first->next();
    }
    inline void insertUpdate(Node *insertNode) {
        if(!first)
            first = insertNode;
    }

    inline Node *getFirst() const { return first; }
    inline Node *getLast() const { return first->prev(); }

private:
    Node *first;
};

#endif // CDLIST_H
