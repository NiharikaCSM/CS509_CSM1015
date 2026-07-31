#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>

int **allocateMatrixSpace(int rows, int cols);
void freeMatrixSpace(int **matrix, int rows);
int **readMatrixFromFile(FILE *filename, int *rows, int *cols);
void printMatrix(int **matrix, int rows, int cols);
int **multiplyMatrices(int **matrixA, int rowsA, int colsA, int **matrixB, int rowsB, int colsB);

#endif