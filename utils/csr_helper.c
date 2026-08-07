#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "csr_helper.h"

static void failWithFormatError(const char *message) {
    fprintf(stderr, "Error: Invalid input file format - %s\n", message);
    exit(1);
}

int readSourceVertex(FILE *filename) {
    char keyword[16];
    int source;
    if (fscanf(filename, "%s %d", keyword, &source) != 2)
        failWithFormatError("expected a 'SOURCE s' line at the end of the file");
 
    if (strcasecmp(keyword, "source") != 0)
        failWithFormatError("expected the keyword 'SOURCE' before the source vertex id");

    return source;
}