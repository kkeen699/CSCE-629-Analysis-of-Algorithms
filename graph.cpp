#include "graph.h"

Graph::Graph(const int nV){
    _nV = nV; _totalE = 0;
    _graph = new Node[nV];
}

Graph::~Graph(){
    for(int i = 0; i < _nV; i++){
        Node *temp = _graph[i]._next;
        while(temp != NULL){
            Node *next = temp->_next;
            temp->_next = NULL;
            delete temp;
            temp = next;
        }
    }
    delete[] _graph;  
}

void Graph::randGenerate(const int deg){
    int bw = 0;

    // make sure the graph is connected, add a cycle
    for(int i = 1; i < _nV; i++){
        bw = rand() % maxBW + 1;
        addEdge(i-1, i, bw);
    }
    bw = rand() % maxBW + 1;
    addEdge(_nV-1, 0, bw);

    // random add edge
    for(int i = 0; i < _nV; i++){
        for(int j = i+2; j < _nV; j++){
            if(rand() % _nV < (deg-2)){
                bw = rand() % maxBW + 1;
                addEdge(i, j, bw);
            }
        }
    }
}

void Graph::randPair(){
    _s = rand() % _nV;
    _t = rand() % _nV;
    while(_t == _s) _t = rand() % _nV;
}

void Graph::addEdge(const int v, const int w, const int bw){
    Node *v1 = new Node(v, w, bw);
    v1->_next = _graph[v]._next;
    _graph[v]._next = v1;
    Node *v2 = new Node(w, v, bw);
    v2->_next = _graph[w]._next;
    _graph[w]._next = v2;
    _totalE += 2;
}

void Graph::printGraph(){
    for(int i = 0; i < _nV; i++){
        Node *v = _graph[i]._next;
        while(v != NULL){
            printf("%d %d %d\n", i, v->_tail, v->_bw);
            v = v->_next;
        }
    }
}