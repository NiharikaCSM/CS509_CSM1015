#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H


#include <stdio.h>
#include "graph.h"

void sortNeighborListsWeighted(CSRGraph *graph);
int getEdgeWeight(const CSRGraph *graph, int u, int v, int *outWeight);
void validateUndirectedWeightedSymmetry(const CSRGraph *graph);
void validateConnected(const CSRGraph *graph);

#endif