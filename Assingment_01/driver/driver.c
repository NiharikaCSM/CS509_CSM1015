#include <stdio.h>
#include "wrapper.h"
#include "matrix.h"

int main(int argc, char *argv[]){
    FILE *matrixFile = openFile(argv[1]);

    //populate matrix A and B
    int rowsA, colsA, rowsB, colsB;
    int **matrixA = readMatrixFromFile(matrixFile, &rowsA, &colsA);
    int **matrixB = readMatrixFromFile(matrixFile, &rowsB, &colsB);

    //Multiply matrices and note the start and end time
    double startTime = getExecutionTime();
    int **resultMatrix = multiplyMatrices(matrixA, rowsA, colsA, matrixB, rowsB, colsB);
    double endTime = getExecutionTime();

    printf("Resultant Matrix:\n");
    printMatrix(resultMatrix, rowsA, colsB);

    printExecutionTime(startTime, endTime);

    freeMatrixSpace(matrixA, rowsA);
    freeMatrixSpace(matrixB, rowsB);
    freeMatrixSpace(resultMatrix, rowsA);

    fclose(matrixFile);
    return 0;
}