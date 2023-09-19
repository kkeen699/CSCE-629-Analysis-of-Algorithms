#ifndef DIJKSTRA
#define DIJKSTRA

#include "graph.h"

int findMax(const int, Vertex&);

void relax(const Graph&, const int, Vertex&);

void dijkstra(const Graph&, const int, const int, bool);

#endif