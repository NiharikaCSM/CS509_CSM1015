#include "floyd_warshall.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FW_INF ((long long)1e15)

static void failFW(const char *msg) {
    fprintf(stderr, "Input format error: %s\n", msg);
    exit(EXIT_FAILURE);
}

long long **readAdjacencyMatrix(FILE *file, int *outVertices) {
    int numOfVertices;
    if (fscanf(file, "%d", &numOfVertices) != 1)
        failFW("expected V on the first line.");
    if (numOfVertices <= 0)
        failFW("number of vertices (V) must be a positive integer.");

    long long **matrix = malloc(sizeof(long long *) * numOfVertices);
    for (int i = 0; i < numOfVertices; i++) {
        matrix[i] = malloc(sizeof(long long) * numOfVertices);
    }

    //value read form matrix (can be either an integer or the literal token INF)
    char token[64];
    for (int i = 0; i < numOfVertices; i++) {
        for (int j = 0; j < numOfVertices; j++) {
            if (fscanf(file, "%63s", token) != 1)
                failFW("matrix ended early or contained a malformed entry."); //value couldn't fit into token buffer
            if (strcmp(token, "INF") == 0) {
                matrix[i][j] = FW_INF;
            } else {
                char *end;
                //converts token to a long long integer, and checks if the entire token was consumed
                long long val = strtoll(token, &end, 10);
                if (*end != '\0')
                    failFW("matrix entry is neither an integer nor the literal token INF.");
                matrix[i][j] = val;
            }
        }
    }

    //validation check for diagonal entries
    for (int i = 0; i < numOfVertices; i++) {
        if (matrix[i][i] != 0)
            failFW("diagonal entry (i, i) must be 0.");
    }

    *outVertices = numOfVertices;
    return matrix;
}

FloydWarshallResult runFloydWarshall(long long **matrix, int vertices) {
    FloydWarshallResult result;
    int numOfVertices = vertices;
    result.vertices = numOfVertices;
    result.negativeCycle = 0;

    result.dist = malloc(sizeof(long long *) * numOfVertices);
    for (int i = 0; i < numOfVertices; i++) {
        result.dist[i] = malloc(sizeof(long long) * numOfVertices);
        //copy the input matrix into the result distance matrix
        memcpy(result.dist[i], matrix[i], sizeof(long long) * numOfVertices); 
    }

    for (int k = 0; k < numOfVertices; k++) {
        for (int i = 0; i < numOfVertices; i++) {
            //if distance is infinite, then there is no point in checking for a path through k
            if (result.dist[i][k] >= FW_INF) continue;
            for (int j = 0; j < numOfVertices; j++) {
                if (result.dist[k][j] >= FW_INF) continue;
                long long through = result.dist[i][k] + result.dist[k][j];
                //update distance matrix to keep the shorter route
                if (through < result.dist[i][j]) {
                    result.dist[i][j] = through;
                }
            }
        }
    }

    //negative cycle detection: if any diagonal entry is negative, then there is a negative cycle
    for (int i = 0; i < numOfVertices; i++) {
        if (result.dist[i][i] < 0) {
            result.negativeCycle = 1;
            break;
        }
    }
    return result;
}

void freeMatrix(long long **matrix, int vertices) {
    for (int i = 0; i < vertices; i++) free(matrix[i]);
    free(matrix);
}

void freeFloydWarshallResult(FloydWarshallResult *result) {
    freeMatrix(result->dist, result->vertices);
    result->dist = NULL;
}

void printFloydWarshallResult(const FloydWarshallResult *result) {
    printf("Algorithm: Floyd-Warshall\n");

    if (result->negativeCycle) {
        printf("Negative cycle: True\n");
    } else {
        printf("Distance matrix:\n");
        for (int i = 0; i < result->vertices; i++) {
            for (int j = 0; j < result->vertices; j++) {
                if (result->dist[i][j] >= FW_INF) {
                    printf("INF");
                } else {
                    printf("%lld", result->dist[i][j]);
                }
                printf(j == result->vertices - 1 ? "\n" : " ");
            }
        }
        printf("Negative cycle: None\n");
    }
}