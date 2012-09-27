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
        if(remove == first /*&& first != first->prev()*/)
        {
//            #ifdef FIBHEAPGRAPHICS_H
            first = first->prev();
//            #else
//            first = first->next();
//            #endif
        }
    }

    inline Node *getFirst() const {
//        #ifdef FIBHEAPGRAPHICS_H
        return first->next();
//        #else
//        return first;
//        #endif
    }
    inline Node *getLast() const {
//        #ifdef FIBHEAPGRAPHICS_H
        return first;
//        #else
//        return first->prev();
//        #endif
    }

private:
    Node *first; // #ifdef FIBHEAPGRAPHICS_H the node is last
};

#endif // CDLIST_H
