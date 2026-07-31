#define WRAPPER.H

#include<stdio.h>
#include<time.h>

//opens files passed via command line
FILE *openFile(int argc, char *argv[]);

//returns the runtime
double getExecutionTime();

double printExecutionTime(double start, double end);

