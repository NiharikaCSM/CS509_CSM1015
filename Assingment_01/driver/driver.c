#include <stdio.h>
#include <string.h>
#include "wrapper.h"
#include "matrix.h"

int main(int argc, char *argv[]){
    FILE *matrixFile = openFile(argv[1]);
    const char *method = argv[2];

    //populate matrix A and B
    int rowsA, colsA, rowsB, colsB;
    getDimensions(matrixFile, &rowsA, &colsA, &colsB);
    rowsB = colsA;
    
    int **matrixA = readMatrixFromFile(matrixFile, &rowsA, &colsA);
    int **matrixB = readMatrixFromFile(matrixFile, &rowsB, &colsB);
    int **resultMatrix = NULL;
    double startTime, endTime;

    if (strcasecmp(method, "simple") == 0) {
        printf("Algorithm: GEMM Simple\n");
        //Multiply matrices and note the start and end time
        startTime = getExecutionTime();
        resultMatrix = multiplyMatricesSimple(matrixA, rowsA, colsA, matrixB, rowsB, colsB);
        endTime = getExecutionTime();

    } else if (strcasecmp(method, "blocking") == 0) {
        printf("Algorithm: GEMM Blocking\n");

    } else {
        printf("Invalid multiplication method specified\n");
        fclose(matrixFile);
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