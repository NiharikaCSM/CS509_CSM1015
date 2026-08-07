#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "bellman_ford.h"
#include "wrapper.h"
#include "../utils/csr_helper.h"

void runBellmanFordFromFile(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Error: could not open input file '%s'\n", path);
        exit(EXIT_FAILURE);
    }

    CSRGraph graph = readAdjacencyListAsCSR(file, 1); //weighted graph

    char keyword[32];
    int source = readSourceVertex(file);
    fclose(file);

    if (source < 0 || source >= graph.vertices) {
        fprintf(stderr, "Error: source vertex %d is out of range\n", source);
        exit(EXIT_FAILURE);
    }

    double startTime = getExecutionTime();
    BellmanFordResult result = runBellmanFord(&graph, source);
    double endTime = getExecutionTime();

    printBellmanFordResult(&result);
    printExecutionTime(startTime, endTime);

    freeBellmanFordResult(&result);
    free(graph.rowPtr);
    free(graph.colIndex);
    free(graph.edgeWeights);
}

