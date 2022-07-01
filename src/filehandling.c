#include <stdio.h>
#include <stdlib.h>

void printHeader(char string[20], char pattern[20]) {
    FILE *fPtr = fopen("data/result.txt", "a");

    if (fPtr == NULL) {
        puts ("Could not open file!");
        exit(-1);
    }

    fprintf(
        fPtr,
        "String: %s\n"
        "Pattern: %s\n",
        string, pattern
    );

    fclose(fPtr);
}

void writeResultToFile(size_t bFOP, size_t hOP) {
    FILE *fPtr = fopen("data/result.txt", "a");

    fprintf(fPtr,
        "\nCritical operations:\n"
        "Brute-force: %d\n"
        "Horspool: %d\n\n"
        "==================================\n"
        "==================================\n\n",
        bFOP, hOP
    );

    fclose(fPtr);
}

