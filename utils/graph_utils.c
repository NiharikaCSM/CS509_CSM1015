#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "csr_helper.h"
#include "graph.h"

typedef struct {
    int neighbor;
    int weight;
} NeighborWeightPair;

static void failWithFormatError(const char *message) {
    fprintf(stderr, "Error: Invalid input file format - %s\n", message);
    exit(1);
}

static int comparePairsByNeighbor(const void *a, const void *b) {
    const NeighborWeightPair *pa = (const NeighborWeightPair *)a;
    const NeighborWeightPair *pb = (const NeighborWeightPair *)b;
    return (pa->neighbor > pb->neighbor) - (pa->neighbor < pb->neighbor);
}

void sortNeighborListsWeighted(CSRGraph *graph) {
    for (int v = 0; v < graph->vertices; v++) {
        int start = graph->rowPtr[v];
        int len = graph->rowPtr[v + 1] - start;
        if (len <= 1) continue;

        NeighborWeightPair *pairs = malloc(sizeof(NeighborWeightPair) * len);
        for (int i = 0; i < len; i++) {
            pairs[i].neighbor = graph->colIndex[start + i];
            pairs[i].weight = graph->edgeWeights[start + i];
        }
        qsort(pairs, len, sizeof(NeighborWeightPair), comparePairsByNeighbor);
        for (int i = 0; i < len; i++) {
            graph->colIndex[start + i] = pairs[i].neighbor;
            graph->edgeWeights[start + i] = pairs[i].weight;
        }
        free(pairs);
    }
}

int getEdgeWeight(const CSRGraph *graph, int u, int v, int *outWeight) {
    int lo = graph->rowPtr[u];
    int hi = graph->rowPtr[u + 1] - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = graph->colIndex[mid];
        if (val == v) {
            *outWeight = graph->edgeWeights[mid];
            return 1;
        }
        if (val < v) lo = mid + 1;
        else hi = mid - 1;
    }
    return 0;
}

void validateUndirectedWeightedSymmetry(const CSRGraph *graph) {
    for (int u = 0; u < graph->vertices; u++) {
        int start = graph->rowPtr[u];
        int end = graph->rowPtr[u + 1];
        for (int e = start; e < end; e++) {
            int v = graph->colIndex[e];
            int wForward = graph->edgeWeights[e];
            int wBackward;
            if (!getEdgeWeight(graph, v, u, &wBackward)) {
                fprintf(stderr,
                    "Error: Invalid input file format - edge (%d, %d) is not "
                    "symmetric: vertex %d's adjacency list does not contain "
                    "vertex %d, but the graph must be undirected.\n",
                    u, v, v, u);
                exit(1);
            }
            if (wBackward != wForward) {
                fprintf(stderr,
                    "Error: Invalid input file format - edge (%d, %d) has "
                    "weight %d, but the reverse edge (%d, %d) has weight %d; "
                    "both directions of an undirected edge must carry the "
                    "same weight.\n",
                    u, v, wForward, v, u, wBackward);
                exit(1);
            }
        }
    }
}

void validateConnected(const CSRGraph *graph) {
    int V = graph->vertices;
    if (V == 0) return;

    int *visited = calloc(V, sizeof(int));
    int *queue = malloc(sizeof(int) * V);
    int qHead = 0, qTail = 0;

    queue[qTail++] = 0;
    visited[0] = 1;
    int reachedCount = 1;

    while (qHead < qTail) {
        int v = queue[qHead++];
        int start = graph->rowPtr[v];
        int end = graph->rowPtr[v + 1];
        for (int e = start; e < end; e++) {
            int w = graph->colIndex[e];
            if (!visited[w]) {
                visited[w] = 1;
                queue[qTail++] = w;
                reachedCount++;
            }
        }
    }

    free(queue);
    free(visited);

    if (reachedCount != V) {
        fprintf(stderr,
            "Error: Invalid input file format - graph is not connected: "
            "only %d of %d vertices are reachable from vertex 0, but MST "
            "requires a connected graph.\n",
            reachedCount, V);
        exit(1);
    }
}