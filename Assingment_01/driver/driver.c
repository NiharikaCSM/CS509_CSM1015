#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gemm_runner.h"
#include "csr_runner.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Please provide correct input arguments.\n");
        return 1;
    }

    char *filePath = argv[1];
    char *method = argv[2];

    if (strcasecmp(method, "csr") == 0) {
        if (argc < 4) {
            printf("Please provide correct input arguments.\n");
            return 1;
        }
        int isWeighted = atoi(argv[3]);
        return runCsrConversion(filePath, isWeighted);
    }

    return runGemm(filePath, method);
}