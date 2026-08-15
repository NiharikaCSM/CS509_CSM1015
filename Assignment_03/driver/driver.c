#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kruskal_runner.h"
#include "prim_runner.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please provide correct input arguments.\n");
        return 1;
    }

    char *filePath = argv[1];
    char *method = argv[2];

    if (strcmp(method, "kruskal") == 0) {
        runKruskalFromFile(filePath);
    } 
    else if (strcmp(method, "prim") == 0) {
        //runPrimFromFile(filePath);
    }        
    else {
        fprintf(stderr, "Error: unknown algorithm '%s'\n", method);
        return EXIT_FAILURE;
    }

    return 0;
}