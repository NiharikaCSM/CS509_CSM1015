#include "bellman_ford.h"
#include <stdio.h>
#include <stdlib.h>

#define BF_INF ((long long)1e15)

BellmanFordResult runBellmanFord(const CSRGraph *graph, int source) {
    BellmanFordResult result;
    int V = graph->vertices;

    result.vertices = V;
    result.source = source;
    result.dist = malloc(sizeof(long long) * V);
    result.reachable = malloc(sizeof(int) * V);
    result.negativeCycle = 0;

    for (int v = 0; v < V; v++) {
        result.dist[v] = BF_INF;
        result.reachable[v] = 0;
    }
    result.dist[source] = 0;
    result.reachable[source] = 1;

    /* V-1 relaxation passes over every edge. */
    for (int pass = 0; pass < V - 1; pass++) {
        int changed = 0;
        for (int u = 0; u < V; u++) {
            if (result.dist[u] == BF_INF) continue; /* nothing to relax from */
            int start = graph->rowPtr[u];
            int end = graph->rowPtr[u + 1];
            for (int e = start; e < end; e++) {
                int v = graph->colIndex[e];
                int w = graph->edgeWeights[e];
                if (result.dist[u] + w < result.dist[v]) {
                    result.dist[v] = result.dist[u] + w;
                    changed = 1;
                }
            }
        }
        if (!changed) break; /* converged early; correctness unaffected */
    }

    /* One extra pass: if any edge can still be relaxed, a negative-weight
     * cycle is reachable from the source. */
    for (int u = 0; u < V && !result.negativeCycle; u++) {
        if (result.dist[u] == BF_INF) continue;
        int start = graph->rowPtr[u];
        int end = graph->rowPtr[u + 1];
        for (int e = start; e < end; e++) {
            int v = graph->colIndex[e];
            int w = graph->edgeWeights[e];
            if (result.dist[u] + w < result.dist[v]) {
                result.negativeCycle = 1;
                break;
            }
        }
    }

    for (int v = 0; v < V; v++) {
        result.reachable[v] = (result.dist[v] != BF_INF);
    }

    return result;
}

void freeBellmanFordResult(BellmanFordResult *result) {
    free(result->dist);
    free(result->reachable);
    result->dist = NULL;
    result->reachable = NULL;
}

void printBellmanFordResult(const BellmanFordResult *result) {
    printf("Algorithm: Bellman-Ford\n");
    printf("Source: %d\n", result->source);

    if (result->negativeCycle) {
        printf("Negative cycle: true\n");
    } else {
        printf("Vertex Distance\n");
        for (int v = 0; v < result->vertices; v++) {
            if (result->reachable[v]) {
                printf("%d %lld\n", v, result->dist[v]);
            } else {
                printf("%d INF\n", v);
            }
        }
        printf("Negative cycle: none\n");
    }
}
