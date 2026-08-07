#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H
#include "graph.h"

typedef struct {
    int vertices;
    int source;
    long long *dist;     //shortest distance from source to each vertex
    int *reachable;      //1 if vertex is reachable from source, else 0
    int negativeCycle;   //1 if a negative-weight cycle reachable from source was found 
} BellmanFordResult;

BellmanFordResult runBellmanFord(const CSRGraph *graph, int source);

void freeBellmanFordResult(BellmanFordResult *result);

void printBellmanFordResult(const BellmanFordResult *result);

#endif