#include <chrono>
#include <algorithm>
#include "dijkstra_heap.h"

#define INF (1 << 20)

MaxHeap::MaxHeap(const int nV){
    _parent = new int[nV]; 
    _bWidth = new int[nV];
    _status = new int[nV];
    _heap = new int[nV]; 
    _pos = new int[nV];
    
    for(int i = 0; i < nV; i++){
        _parent[i] = -1;
        _bWidth[i] = 0;
        _status[i] = -1;
        _pos[i] = -1;
        _heap[i] = -1;
    }
    _size = 0;
}

MaxHeap::~MaxHeap(){
    delete [] _parent;
    delete [] _bWidth;
    delete [] _status;
    delete [] _heap;
    delete [] _pos;
}

void MaxHeap::insert(const int v){
    _size++;
    int n = _size - 1;
    while(n >= 1){
        int parent = (n-1)/2;
        if(_bWidth[_heap[parent]] >= _bWidth[v]) break;
        else{
            _heap[n] = _heap[parent];
            _pos[_heap[parent]] = n;
            n = parent;  
        }
    }
    _heap[n] = v;
    _pos[v] = n;
}

void MaxHeap::del(const int v){
    int n = _pos[v];
    _pos[v] = -1;
    int i = _heap[_size-1]; 
    _size--;
    while(n >= 1){
        int parent = (n-1)/2;
        if(_bWidth[_heap[parent]] >= _bWidth[i]) break;
        else{
            _heap[n] = _heap[parent];
            _pos[_heap[parent]] = n;
            n = parent;
        }
    }
    while(2*n+1 < _size){
        int child = 2*n+1;
        if(2*n+2 < _size && _bWidth[_heap[2*n+2]] > _bWidth[_heap[2*n+1]])
            child = 2*n+2;
        if( _bWidth[i] >= _bWidth[_heap[child]]) break;
        else{
            _heap[n] = _heap[child];
            _pos[_heap[child]] = n;
            n = child;
        }
    }
    _heap[n] = i;
    _pos[i] = n; 
}

void relax_maxHeap(const int v, const Graph& G, MaxHeap& maxheap){
    Node *addV = G._graph[v]._next;
    while(addV != NULL){
        int w = addV->_tail;
        if(maxheap._status[w] != 1 && 
           maxheap._bWidth[w] < min(maxheap._bWidth[v], addV->_bw)){
            if(maxheap._status[w] == 0) maxheap.del(w);
            maxheap._bWidth[w] = min(maxheap._bWidth[v], addV->_bw);
            maxheap._parent[w] = v;
            maxheap.insert(w);
            maxheap._status[w] = 0;
        }
        addV = addV->_next;
    }
}

void dijkstra_maxHeap(const Graph& G, const int s, const int t, bool show){
    auto start = chrono::high_resolution_clock::now();
    const int nV = G._nV;

    MaxHeap maxheap(nV);
    maxheap._bWidth[s] = INF;
    maxheap.insert(s);

    for(int i = 0; i < nV; i++){
        int addV = maxheap.max();
        if(addV == -1) break;
        maxheap.del(addV);
        maxheap._status[addV] = 1;
        relax_maxHeap(addV, G, maxheap);
    }

    auto stop = chrono::high_resolution_clock::now();
    long long int duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    printf("Dijkstra_Heap\ntime: %lld\n", duration);
    
    if(show){
        printf("max bandwidth: %d\n", maxheap._bWidth[t]);
        int temp = t;
        while(temp != -1){
            printf("%d <- ", temp);
            temp = maxheap._parent[temp];
        }
        printf("\n");
    }
}