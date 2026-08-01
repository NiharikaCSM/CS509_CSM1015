#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>

int **allocateMatrixSpace(int rows, int cols);
void freeMatrixSpace(int **matrix, int rows);
void getDimensions(FILE *filename, int *rowsA, int *colsA_rowsB, int *colsB);
int **readMatrixFromFile(FILE *filename, int *rows, int *cols);
void printMatrix(int **matrix, int rows, int cols);
int **multiplyMatricesSimple(int **matrixA, int rowsA, int colsA, int **matrixB, int rowsB, int colsB);

#endif