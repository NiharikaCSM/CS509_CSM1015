#include <stdio.h>
#include "csr_runner.h"
#include "wrapper.h"
#include "graph.h"

int runCsrConversion(char *graphFilePath, int isWeighted) {
    FILE *graphFile = openFile(graphFilePath);

    printf("Algorithm: CSR Conversion\n");

    double startTime = getExecutionTime();
    CSRGraph graph = readAdjacencyListAsCSR(graphFile, isWeighted);
    double endTime = getExecutionTime();

    fclose(graphFile);
    printCSRGraph(&graph);
    printExecutionTime(startTime, endTime);
    freeCSRGraph(&graph);

    return 0;
}