#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <stdlib.h>
#include <unordered_set>
#include <time.h>
using namespace std;

#define maxBW 5000

class Vertex{
public:
    Vertex(const int nV){
        _parent = new int[nV];
        _bWidth = new int[nV];
        _status = new bool[nV];
        for(int i = 0; i < nV; i++){
            _parent[i] = -1; _bWidth[i] = 0; _status[i] = false;
        }
    }
    ~Vertex(){
        delete [] _parent;
        delete [] _bWidth;
        delete [] _status;
    }

    int *_parent;
    int *_bWidth;
    bool *_status;
};

class Node{
public:
    Node(){_next = NULL;}
    Node(const int head, const int tail, const int bw){
        _head = head;
        _tail = tail;
        _bw = bw;
        _next = NULL;
    }
    int _head;
    int _tail;
    int _bw;
    Node *_next;
};


class Graph{
public:
    Graph(const int);
    ~Graph();

    void randGenerate(const int);
    void addEdge(const int, const int, const int);
    void randPair();
    void printGraph();
    
    int _nV;
    int _totalE;
    int _s;
    int _t;
    Node *_graph;
};

#endif