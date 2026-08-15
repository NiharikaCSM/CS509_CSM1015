#include "kruskal_runner.h"
#include "graph.h"
#include "wrapper.h"
#include "kruskal.h"
#include "graph_utils.h"
#include <stdio.h>
#include <stdlib.h>

void runKruskalFromFile(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Error: could not open input file '%s'\n", path);
        exit(EXIT_FAILURE);
    }

    CSRGraph graph = readAdjacencyListAsCSR(file, 1); //weighted graph
    fclose(file);

    sortNeighborListsWeighted(&graph);
    validateUndirectedWeightedSymmetry(&graph);
    validateConnected(&graph);

    double startTime = getExecutionTime();
    KruskalResult result = runKruskal(&graph);
    double endTime = getExecutionTime();

    printKruskalResult(&result);
    printExecutionTime(startTime, endTime);

    freeKruskalResult(&result);
    free(graph.rowPtr);
    free(graph.colIndex);
    free(graph.edgeWeights);
}