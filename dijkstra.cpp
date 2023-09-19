#include <chrono>
#include <algorithm>
#include "dijkstra.h"

#define INF (1 << 20)

int findMax(const int nV, Vertex& vertex){
    int next = -1, max = 0;
    for(int i = 0; i < nV; i++){
        if(!vertex._status[i] && vertex._bWidth[i] > max){
            next = i;
            max = vertex._bWidth[i];
        }
    }
    return next;
}

void relax(const Graph& G, const int v, Vertex& vertex){
    Node *addV = G._graph[v]._next;
    while(addV != NULL){
        if(!vertex._status[addV->_tail] && 
           vertex._bWidth[addV->_tail] < min(vertex._bWidth[v], addV->_bw)){
            vertex._bWidth[addV->_tail] = min(vertex._bWidth[v], addV->_bw);
            vertex._parent[addV->_tail] = v;
        }
        addV = addV->_next;
    }
}

void dijkstra(const Graph& G, const int s, const int t, bool show){
    auto start = chrono::high_resolution_clock::now();
    const int nV = G._nV;

    Vertex vertex(nV);
    vertex._bWidth[s] = INF;

    for(int i = 0; i < nV; i++){
        int addV = findMax(nV, vertex);
        if(addV == -1) break;
        vertex._status[addV] = true;
        relax(G, addV, vertex);
    }
    
    auto stop = chrono::high_resolution_clock::now();
    long long int duration = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    printf("Dijkstra\ntime: %lld\n", duration);
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