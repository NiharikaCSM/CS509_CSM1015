#include "bellman_ford.h"
#include <stdio.h>
#include <stdlib.h>

#define BF_INF ((long long)1e15)

BellmanFordResult runBellmanFord(const CSRGraph *graph, int source) {
    BellmanFordResult result;
    int numOfVertices = graph->vertices;

    result.vertices = numOfVertices;
    result.source = source;
    result.dist = malloc(sizeof(long long) * numOfVertices);
    result.reachable = malloc(sizeof(int) * numOfVertices);
    result.negativeCycle = 0;

    for (int v = 0; v < numOfVertices; v++) {
        //initialize all distances to infinity and reachable to false
        result.dist[v] = BF_INF;
        result.reachable[v] = 0;
    }
    result.dist[source] = 0;
    result.reachable[source] = 1;

    //V-1 passes over every edge. It guarentees shortest path if no negative cycle is reachable from source.
    for (int pass = 0; pass < numOfVertices - 1; pass++) {
        int changed = 0;
        for (int u = 0; u < numOfVertices; u++) {
            if (result.dist[u] == BF_INF) continue; //nothing to relax from

            //else find all edges from u and relax them
            int start = graph->rowPtr[u];
            int end = graph->rowPtr[u + 1];
            for (int e = start; e < end; e++) {
                int neighbor = graph->colIndex[e];
                int weight = graph->edgeWeights[e];
                if (result.dist[u] + weight < result.dist[neighbor]) {
                    result.dist[neighbor] = result.dist[u] + weight;
                    changed = 1;
                }
            }
        }
        //if a full pass relaxes nothing, implies that all shortest paths have been found and we can stop early
        if (!changed) break; 
    }

    //Vth pass to check for negative cycles reachable from source
    for (int u = 0; u < numOfVertices && !result.negativeCycle; u++) {
        if (result.dist[u] == BF_INF) continue;
        int start = graph->rowPtr[u];
        int end = graph->rowPtr[u + 1];
        for (int e = start; e < end; e++) {
            int neighbor = graph->colIndex[e];
            int weight = graph->edgeWeights[e];

            //if there is a relaxation possible, implies a negative cycle reachable from source exists
            if (result.dist[u] + weight < result.dist[neighbor]) {
                result.negativeCycle = 1;
                break;
            }
        }
    }

    for (int v = 0; v < numOfVertices; v++) {
        result.reachable[v] = (result.dist[v] != BF_INF); //1 if reachable, else 0
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
        printf("Negative cycle: True\n");
    } else {
        printf("Vertex Distance\n");
        for (int v = 0; v < result->vertices; v++) {
            if (result->reachable[v]) {
                printf("%d %lld\n", v, result->dist[v]);
            } else {
                printf("%d INF\n", v);
            }
        }
        printf("Negative cycle: None\n");
    }

}
