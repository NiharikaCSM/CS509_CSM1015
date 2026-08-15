#include "prims.h"
#include "min_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PRIM_INF INT_MAX

PrimResult runPrim(const CSRGraph *graph) {
    PrimResult result;
    int V = graph->vertices;
    result.edges = malloc(sizeof(MSTEdge) * (V > 0 ? V - 1 : 0));
    result.edgeCount = 0;
    result.totalWeight = 0;

    int *key = malloc(sizeof(int) * V);      //cheapest known edge weight into the tree 
    int *parent = malloc(sizeof(int) * V);   //the tree-side endpoint of that cheapest edge 
    int *inTree = calloc(V, sizeof(int));

    for (int v = 0; v < V; v++) {
        key[v] = PRIM_INF;
        parent[v] = -1;
    }

    int heapCapacity = graph->rowPtr[V] + 1;
    MinHeap heap = heapCreate(heapCapacity);

    int start = 0; 
    key[start] = 0;
    heapPush(&heap, 0, start);

    while (!heapEmpty(&heap)) {
        HeapEntry top;
        heapPop(&heap, &top);
        int u = top.vertex;

        if (inTree[u]) continue;          
        if (top.key != key[u]) continue;  

        inTree[u] = 1;
        if (parent[u] != -1) {
            result.edges[result.edgeCount].u = parent[u];
            result.edges[result.edgeCount].v = u;
            result.edges[result.edgeCount].weight = key[u];
            result.edgeCount++;
            result.totalWeight += key[u];
        }

        int rowStart = graph->rowPtr[u];
        int rowEnd = graph->rowPtr[u + 1];
        for (int e = rowStart; e < rowEnd; e++) {
            int w = graph->colIndex[e];
            int weight = graph->edgeWeights[e];
            if (!inTree[w] && weight < key[w]) {
                key[w] = weight;
                parent[w] = u;
                heapPush(&heap, weight, w);
            }
        }
    }
    heapFree(&heap);
    free(inTree);
    free(parent);
    free(key);

    return result;
}

void freePrimResult(PrimResult *result) {
    free(result->edges);
    result->edges = NULL;
}

void printPrimResult(const PrimResult *result) {
    printf("Algorithm: Prim's MST\n");
    printf("MST edges:\n");
    for (int i = 0; i < result->edgeCount; i++) {
        printf("%d %d %d\n", result->edges[i].u, result->edges[i].v, result->edges[i].weight);
    }
    printf("Total MST weight: %lld\n", result->totalWeight);
}