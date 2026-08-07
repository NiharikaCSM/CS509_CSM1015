#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "bf_runner.h"
//#include "fw_runner.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Please provide correct input arguments.\n");
        return 1;
    }

    char *filePath = argv[1];
    char *method = argv[2];

    if (strcmp(method, "bf") == 0) {
        runBellmanFordFromFile(filePath);
    } 
    else if (strcmp(method, "fw") == 0) {
        //runFloydWarshallFromFile(filePath);
    }     
    else {
        fprintf(stderr, "Error: unknown algorithm '%s'\n", method);
        return EXIT_FAILURE;
    }

    return 0;
}
