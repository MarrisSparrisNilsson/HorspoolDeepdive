#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ASCII_SIZE 128

void shiftTable(int *table, char pattern[]);
int horspoolMatching(char pattern[], char string[], size_t *hOP);
int bruteForceMatching(char pattern[], char string[], size_t *bFOP);

#endif