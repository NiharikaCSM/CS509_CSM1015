#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <stdio.h>

typedef struct {
    int vertices;
    long long **dist;   //V x V distance matrix
    int negativeCycle;   //1 if dist[i][i] < 0 for some i after the run
} FloydWarshallResult;

//directly reads the input file, not the CSR representation
long long **readAdjacencyMatrix(FILE *file, int *outVertices);

FloydWarshallResult runFloydWarshall(long long **matrix, int vertices);

void freeFloydWarshallResult(FloydWarshallResult *result);
void freeMatrix(long long **matrix, int vertices);
void printFloydWarshallResult(const FloydWarshallResult *result);

#endif 