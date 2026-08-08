#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "floyd_warshall.h"
#include "wrapper.h"

void runFloydWarshallFromFile(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "Error: could not open input file '%s'\n", path);
        exit(EXIT_FAILURE);
    }

    int vertices;
    double startTime, endTime;
    long long **matrix = readAdjacencyMatrix(file, &vertices);
    fclose(file);

    startTime = getExecutionTime();
    FloydWarshallResult result = runFloydWarshall(matrix, vertices);
    endTime = getExecutionTime();

    printFloydWarshallResult(&result);
    printExecutionTime(startTime, endTime);

    freeFloydWarshallResult(&result);
    freeMatrix(matrix, vertices);
}