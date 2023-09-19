#include <iostream>
#include <string.h>
#include "graph.h"
#include "dijkstra.h"
#include "dijkstra_heap.h"
#include "kruskal.h"
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 4){
        printf("please enter ./graph [vertex] [degree] true/false\n");
        return 0;
    }
    int nV = atoi(argv[1]), deg = atoi(argv[2]);
    srand(time(NULL));
    Graph g1(nV);
    g1.randGenerate(deg);
    if(strcmp(argv[3], "true") == 0){
        g1.printGraph();
        g1.randPair();
        printf("s: %d, t: %d\n", g1._s, g1._t);
        dijkstra(g1, g1._s, g1._t, true);
        dijkstra_maxHeap(g1, g1._s, g1._t, true);
        kruskal(g1, g1._s, g1._t, true);
    }
    else if(strcmp(argv[3], "false") == 0){
        for(int i = 0; i < 5; i++){
            g1.randPair(); 
            dijkstra(g1, g1._s, g1._t, false);
            dijkstra_maxHeap(g1, g1._s, g1._t, false);
            kruskal(g1, g1._s, g1._t, false);
            printf("=================\n");
        }
    }
    return 0;
}