#include <stdio.h>
#include "csr_runner.h"
#include "wrapper.h"
#include "graph.h"

int runCsrConversion(char *graphFilePath, int isWeighted) {
    FILE *graphFile = openFile(graphFilePath);

    printf("Algorithm: CSR Conversion\n");

    CSRGraph graph = readAdjacencyListAsCSR(graphFile, isWeighted);

    fclose(graphFile);
    printCSRGraph(&graph);
    freeCSRGraph(&graph);

    return 0;
}