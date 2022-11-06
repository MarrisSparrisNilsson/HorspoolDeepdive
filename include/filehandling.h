
#ifndef FILEHANDLING_H_ /* Include guard */
#define FILEHANDLING_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_SIZE 4000

void printHeader(size_t inputSize, char string[20], char pattern[20], int test);
void writeResultToFile(size_t bFOP, size_t hOP);
void readInputFile(char *text, int type);
void printWorstCaseHeader(size_t inputSize, char pattern[], int algo, int test);
void printAverageCaseHeader(size_t inputSize, int algo, int test);
void printResult(char pattern[], int index, int op);
void printSummary(size_t averageOP);


#endif
