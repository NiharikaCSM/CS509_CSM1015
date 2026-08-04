#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

#define BLOCK_SIZE 32

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

void getDimensions(FILE *filename, int *rowsA, int *colsA, int *colsB){
    char headerLine[256];
    if(fgets(headerLine, sizeof(headerLine), filename) == NULL) {
        printf("Error: Failed to read matrix dimensions\n");
        exit(1);
    }
    if (sscanf(headerLine, "%d %d %d", rowsA, colsA, colsB) != 3) {
        printf("Error: Matrix dimensions not found on the first line\n");
        exit(1);
    }
}

int **readMatrixFromFile(FILE *filename, int *rows, int *cols) {
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

int **multiplyMatricesSimple(int **matrixA, int rowsA, int colsA, int **matrixB, int rowsB, int colsB) {
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

int **multiplyMatricesBlocking(int **matrixA, int rowsA, int colsA, int **matrixB, int colsB) {
    int **resultMatrix = allocateMatrixSpace(rowsA, colsB);

    // Initialize result matrix to all zeros
    for (int row = 0; row < rowsA; row++)
        for (int col = 0; col < colsB; col++)
            resultMatrix[row][col] = 0;

    // Outer three loops walk through the matrix in BLOCK_SIZE x BLOCK_SIZE chunks
    for (int rowBlockStart = 0; rowBlockStart < rowsA; rowBlockStart += BLOCK_SIZE) {
        for (int colBlockStart = 0; colBlockStart < colsB; colBlockStart += BLOCK_SIZE) {
            for (int innerBlockStart = 0; innerBlockStart < colsA; innerBlockStart += BLOCK_SIZE) {

                // Clamp block boundaries so we don't run past the matrix edges
                int rowBlockEnd = (rowBlockStart + BLOCK_SIZE < rowsA) ? rowBlockStart + BLOCK_SIZE : rowsA;
                int colBlockEnd = (colBlockStart + BLOCK_SIZE < colsB) ? colBlockStart + BLOCK_SIZE : colsB;
                int innerBlockEnd = (innerBlockStart + BLOCK_SIZE < colsA) ? innerBlockStart + BLOCK_SIZE : colsA;

                // Inner three loops do the actual multiplication, but only within the current block
                for (int row = rowBlockStart; row < rowBlockEnd; row++) {
                    for (int col = colBlockStart; col < colBlockEnd; col++) {
                        int partialSum = resultMatrix[row][col];
                        for (int inner = innerBlockStart; inner < innerBlockEnd; inner++)
                            partialSum += matrixA[row][inner] * matrixB[inner][col];
                        resultMatrix[row][col] = partialSum;
                    }
                }
            }
        }
    }
    return resultMatrix;
}