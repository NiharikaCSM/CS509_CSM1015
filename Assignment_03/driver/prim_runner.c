#include "prim_runner.h"
#include "graph.h"
#include "graph_utils.h"
#include "wrapper.h"
#include "prims.h"
#include <stdio.h>
#include <stdlib.h>

void runPrimFromFile(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Error: could not open input file '%s'\n", path);
        exit(EXIT_FAILURE);
    }

    CSRGraph graph = readAdjacencyListAsCSR(file, 1); //weighted input
    fclose(file);

    sortNeighborListsWeighted(&graph);
    validateUndirectedWeightedSymmetry(&graph);
    validateConnected(&graph);

    double startTime = getExecutionTime();
    PrimResult result = runPrim(&graph);
    double endTime = getExecutionTime();

    printPrimResult(&result);
    printExecutionTime(startTime, endTime);

    freePrimResult(&result);
    free(graph.rowPtr);
    free(graph.colIndex);
    free(graph.edgeWeights);
}