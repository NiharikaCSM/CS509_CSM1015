#include <stdio.h>
#include <stdlib.h>
#include "wrapper.h"

FILE *openFile(const char *filename) {
    FILE *inputFile = fopen(filename, "r");
    if(!inputFile) {
        printf("Error : Failed to open file\n");
        exit(1);
    }
    return inputFile;
}

double getExecutionTime() {
    return (double)clock() / CLOCKS_PER_SEC;
}

void printExecutionTime(double start, double end) {
    printf("\nExecution Time : %.6f seconds", end-start);
}