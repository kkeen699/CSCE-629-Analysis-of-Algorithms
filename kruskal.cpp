#include <chrono>
#include <vector>
#include <algorithm>
#include <ctime>
#include "kruskal.h"

#define INF (1 << 20)

HeapSort::HeapSort(const int nE){
    _heap = new Node* [nE]; 
    _size = 0;
}

HeapSort::~HeapSort(){
    delete [] _heap;
}

Node* HeapSort::pop_max(){
    if(_size == 0) return NULL;
    Node *max = _heap[0];
    int n = 0;
    Node *temp = _heap[_size-1];
    _size--;
    while(2*n+1 < _size){
        int child = 2*n+1;
        if(2*n+2 < _size && _heap[2*n+2]->_bw > _heap[2*n+1]->_bw)
            child = 2*n+2;
        if(temp->_bw >= _heap[child]->_bw) break;
        else{
            _heap[n] = _heap[child];
            n = child;
        }
    }
    _heap[n] = temp;
    return max; 
}

void HeapSort::insert(Node *v){
    _size++;
    int n = _size - 1;
    while(n >= 1){
        int parent = (n-1)/2;
        if(_heap[parent]->_bw >= v->_bw) break;
        else{
            _heap[n] = _heap[parent];
            n = parent;  
        }
    }
    _heap[n] = v;
}

int find(const int v, int* root){
    vector<int> path;
    int r = v;
    while(r != root[r]){
        path.push_back(r);
        r = root[r];
    }
    for(size_t i = 0; i < path.size(); i++){
        int temp = path[i];
        root[temp] = r;
    }
    return r;
}

void MaxSpanningTree(const Graph& G, Graph& MSTree, const int nV, const int nE){
    HeapSort maxheap(nE);
    int count = 0;
    for(int i = 0; i < nV; i++){
        Node *temp = G._graph[i]._next;
        while(temp != NULL){
            maxheap.insert(temp);
            temp = temp->_next;
            count += 1;
        }
    }
    
    int *root = new int[nV];
    int *rank = new int[nV];
    for(int i = 0; i < nV; i++){
        root[i] = i; rank[i] = 0;
    }
    
    for(int i = 0; i < nE; i++){
        Node *edge = maxheap.pop_max();
        const int v = edge->_head;
        const int u = edge->_tail;
        const int r1 = find(v, root), r2 = find(u, root);
        if(r1 != r2){
            if(rank[r1] > rank[r2]) root[r2] = r1;
            else if(rank[r1] < rank[r2]) root[r1] = r2;
            else {root[r1] = r2; rank[r2]++;}
            MSTree.addEdge(v, u, edge->_bw);
        }
    }
    
    delete [] rank; 
    delete [] root;
}

void DFS(const Graph& MSTree, const int v, Vertex& vertex){
    vertex._status[v] = true;
    Node* temp = MSTree._graph[v]._next;
    while(temp != NULL){
        if(!vertex._status[temp->_tail]){
            vertex._parent[temp->_tail] = v;
            vertex._bWidth[temp->_tail] = min(vertex._bWidth[v], temp->_bw);
            DFS(MSTree, temp->_tail, vertex);
        }
        temp = temp->_next;
    }
}

void kruskal(const Graph& G, const int s, const int t, bool show){
    auto start = chrono::high_resolution_clock::now();

    Graph MSTree(G._nV);
    MaxSpanningTree(G, MSTree, G._nV, G._totalE);
    
    Vertex vertex(G._nV);
    vertex._bWidth[s] = INF;
    
    DFS(MSTree, s, vertex);

    auto stop = chrono::high_resolution_clock::now();
    long long int duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    printf("Kruskal\ntime: %lld\n", duration);

    if(show){
        printf("max bandwidth: %d\n", vertex._bWidth[t]);
        int temp = t;
        while(temp != -1){
            printf("%d <- ", temp);
            temp = vertex._parent[temp];
        }
        printf("\n");
    }
}