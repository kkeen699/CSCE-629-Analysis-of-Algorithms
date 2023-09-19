#ifndef DIJKSTRA_HEAP
#define DIJKSTRA_HEAP

#include "graph.h"

class MaxHeap{
public:
    MaxHeap(const int);
    ~MaxHeap();
    int max() const {
        return _size > 0 ? _heap[0] : -1;
    }
    void insert(const int v);
    void del(const int v);

    int* _parent;
    int* _bWidth;
    int* _status;
private:
    int* _heap;
    int* _pos;
    int _size;
  };

void relax_maxHeap(const int, const Graph&, MaxHeap&);

void dijkstra_maxHeap(const Graph&, const int, const int, bool);

#endif