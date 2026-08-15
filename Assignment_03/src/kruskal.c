#include "kruskal.h"
#include "dsu.h"
#include "graph_utils.h"
#include <stdio.h>
#include <stdlib.h>

//comparator for qsort
static int compareEdgesByWeight(const void *a, const void *b) {
    const MSTEdge *ea = (const MSTEdge *)a;
    const MSTEdge *eb = (const MSTEdge *)b;
    return (ea->weight > eb->weight) - (ea->weight < eb->weight);
}

KruskalResult runKruskal(const CSRGraph *graph) {
    KruskalResult result;
    int V = graph->vertices;
    // edges array is of size V-1
    result.edges = malloc(sizeof(MSTEdge) * (V > 0 ? V - 1 : 0));
    result.edgeCount = 0;
    result.totalWeight = 0;

    int totalDirectedEntries = graph->rowPtr[V];
    MSTEdge *allEdges = malloc(sizeof(MSTEdge) * totalDirectedEntries);
    int edgeListSize = 0;

    for (int u = 0; u < V; u++) {
        int start = graph->rowPtr[u];
        int end = graph->rowPtr[u + 1];
        for (int e = start; e < end; e++) {
            int v = graph->colIndex[e];
            if (u < v) {
                allEdges[edgeListSize].u = u;
                allEdges[edgeListSize].v = v;
                allEdges[edgeListSize].weight = graph->edgeWeights[e];
                edgeListSize++;
            }
        }
    }

    qsort(allEdges, edgeListSize, sizeof(MSTEdge), compareEdgesByWeight);

    DSU dsu = dsuCreate(V);

    for (int i = 0; i < edgeListSize && result.edgeCount < V - 1; i++) {
        int u = allEdges[i].u;
        int v = allEdges[i].v;
        int w = allEdges[i].weight;
        if (dsuUnion(&dsu, u, v)) {
            result.edges[result.edgeCount].u = u;
            result.edges[result.edgeCount].v = v;
            result.edges[result.edgeCount].weight = w;
            result.edgeCount++;
            result.totalWeight += w;
        }
    }

    dsuFree(&dsu);
    free(allEdges);

    return result;
}

void freeKruskalResult(KruskalResult *result) {
    free(result->edges);
    result->edges = NULL;
}

void printKruskalResult(const KruskalResult *result) {
    printf("Algorithm: Kruskal's MST\n");
    printf("MST edges:\n");
    for (int i = 0; i < result->edgeCount; i++) {
        printf("%d %d %d\n", result->edges[i].u, result->edges[i].v, result->edges[i].weight);
    }
    printf("Total MST weight: %lld\n", result->totalWeight);
}