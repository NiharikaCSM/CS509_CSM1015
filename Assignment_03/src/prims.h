#ifndef PRIM_H
#define PRIM_H

#include "graph.h"
#include "kruskal.h" 

typedef struct {
    MSTEdge *edges;   
    int edgeCount;
    long long totalWeight;
} PrimResult;

PrimResult runPrim(const CSRGraph *graph);

void freePrimResult(PrimResult *result);
void printPrimResult(const PrimResult *result);

#endif 