#ifndef WRAPPER_H
#define WRAPPER_H

#include<stdio.h>
#include<time.h>

//opens files passed via command line
FILE *openFile(const char *filename);

//returns the runtime
double getExecutionTime();

void printExecutionTime(double start, double end);
#endif
