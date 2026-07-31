#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int **allocateMatrixSpace(int rows, int cols) {
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

void freeMatrixSpace(int **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int **readMatrixFromFile(FILE *filename, int *rows, int *cols) {
    fscanf(filename, "%d %d", rows, cols);
    int **matrix = allocateMatrixSpace(*rows, *cols);
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            fscanf(filename, "%d", &matrix[i][j]);
        }
    }
    return matrix;
}

void printMatrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int **multiplyMatrices(int **matrixA, int rowsA, int colsA, int **matrixB, int rowsB, int colsB) {
    if (colsA != rowsB) {
        printf("Incompatible matrix dimensions\n");
        exit(1);
    }

    int **result = allocateMatrixSpace(rowsA, colsB);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return result;
}