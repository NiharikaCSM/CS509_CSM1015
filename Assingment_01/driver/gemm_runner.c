#include <stdio.h>
#include <string.h>
#include "gemm_runner.h"
#include "wrapper.h"
#include "matrix.h"

int runGemm(char *matrixFilePath, char *method) {
    FILE *matrixFile = openFile(matrixFilePath);

    int rowsA, colsA, rowsB, colsB;
    getDimensions(matrixFile, &rowsA, &colsA, &colsB);
    rowsB = colsA;
    int **matrixA = readMatrixFromFile(matrixFile, &rowsA, &colsA);
    int **matrixB = readMatrixFromFile(matrixFile, &rowsB, &colsB);
    int **resultMatrix = NULL;
    double startTime, endTime;

    if (strcasecmp(method, "simple") == 0) {
        printf("Algorithm: GEMM Simple\n");
        startTime = getExecutionTime();
        resultMatrix = multiplyMatricesSimple(matrixA, rowsA, colsA, matrixB, rowsB, colsB);
        endTime = getExecutionTime();

    } else if (strcasecmp(method, "blocking") == 0) {
        printf("Algorithm: GEMM Blocking\n");
        startTime = getExecutionTime();
        resultMatrix = multiplyMatricesBlocking(matrixA, rowsA, colsA, matrixB, colsB);
        endTime = getExecutionTime();

    } else {
        printf("Invalid multiplication method specified\n");
        fclose(matrixFile);
        freeMatrixSpace(matrixA, rowsA);
        freeMatrixSpace(matrixB, rowsB);
        return 1;
    }

    printf("Resultant Matrix:\n");
    printMatrix(resultMatrix, rowsA, colsB);

    printExecutionTime(startTime, endTime);

    freeMatrixSpace(matrixA, rowsA);
    freeMatrixSpace(matrixB, rowsB);
    freeMatrixSpace(resultMatrix, rowsA);
    fclose(matrixFile);

    return 0;
}