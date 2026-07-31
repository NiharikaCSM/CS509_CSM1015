#include <stdio.h>
#include <stdlib.h>
#include "wrapper.h"

FILE *openFile(int argc, char *argv[]){
    if(argc<2) printf("No file passed");

    FILE *inputFile = fopen(argv[1], "r")
    if(!inputFile) {
        printf("Error : Failed to open file");
        exit(1);
    }
    return inputFile;
}

double getExecutionTime()
    return (double)clock() / CLOCKS_PER_SEC;

double printExecutionTime(double start, double end)
    printf("\nExecution Time : %.6f seconds", end-start);