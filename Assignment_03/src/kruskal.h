#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"

typedef struct {
    int u, v, weight;
} MSTEdge;

typedef struct {
    MSTEdge *edges;   
    int edgeCount;
    long long totalWeight;
} KruskalResult;

KruskalResult runKruskal(const CSRGraph *graph);

void freeKruskalResult(KruskalResult *result);
void printKruskalResult(const KruskalResult *result);

#endif