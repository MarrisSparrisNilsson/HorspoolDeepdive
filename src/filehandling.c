#include <stdio.h>
#include <stdlib.h>

void printHeader(int inputSize) {
    FILE *fPtr = fopen("data/result.txt", "a");

    fprintf(fPtr, "Input size: %d\nOP: \n");

    fclose(fPtr);
}

void writeResultToFile(size_t bFOP, size_t hOP) {
    FILE *fPtr = fopen("data/result.txt", "a");

    fprintf(fPtr, "Brute-force: %d\n Horspool: %d\n", bFOP, hOP);

    fclose(fPtr);
}