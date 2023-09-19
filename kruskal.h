#ifndef KRUSKAL
#define KRUSKAL

#include "graph.h"

class HeapSort{
public:
    HeapSort(const int);
    ~HeapSort();
    Node* pop_max();
    void insert(Node*);

private:
    Node** _heap;
    int _size;
};


int find(const int v, int* root);

void MaxSpanningTree(const Graph&, Graph&, const int, const int);

void DFS(const Graph&, const int, Vertex&);

void kruskal(const Graph&, const int, const int, bool);

#endif