#include "filehandling.h"

void printHeader(size_t inputSize, char string[], char pattern[], int test) {
    FILE *fPtr = fopen("data/result.txt", "a");

    if (fPtr == NULL) {
        puts ("Could not open file!");
        exit(-1);
    }

    fprintf(
        fPtr,
        "Input size: %d\n"
        "Test: %d\n"
        "String: %s\n"
        "Pattern: %s\n",
        inputSize, test, string, pattern
    );

    fclose(fPtr);
}

void printWorstCaseHeader(size_t inputSize, char pattern[], int algo, int test) {
    FILE *fPtr = fopen("data/result.txt", "a");

    if (fPtr == NULL) {
        puts ("Could not open file!");
        exit(-1);
    }

    fprintf(
        fPtr,
        "%s (Worst case)\n"
        "Input size: %d\n"
        "Test: %d\n"
        "Pattern: %s\n"
        "Critical operations || Found at index\n"
        "------------------------------------------------\n",
        algo == 1 ? "Brute-force" : "Horspool",
        inputSize,
        test,
        pattern
    );

    fclose(fPtr);
}


void printAverageCaseHeader(size_t inputSize, int algo, int test) {
    FILE *fPtr = fopen("data/result.txt", "a");

    if (fPtr == NULL) {
        puts ("Could not open file!");
        exit(-1);
    }

    fprintf(
        fPtr,
        "%s (Average case)\n"
        "Input size: %d\n"
        "Test: %d\n"
        "Pattern || Found at index || Critical operations\n"
        "------------------------------------------------\n",
        algo == 1 ? "Brute-force" : "Horspool",
        inputSize,
        test
    );

    fclose(fPtr);
}

void printResult(char pattern[], int index, int op) {
    FILE *fPtr = fopen("data/result.txt", "a");

    if (fPtr == NULL) {
        puts ("Could not open file!");
        exit(-1);
    }

    fprintf(
        fPtr,
        "%20s || %4d || %d\n",
        pattern, index, op
    );

    fclose(fPtr);
}

void printSummary(size_t averageOP) {
    FILE *fPtr = fopen("data/result.txt", "a");

    fprintf(fPtr,
        "------------------------------------------------"
        "\nAverage critical operations: %d\n\n"
        "======================================================\n"
        "======================================================\n\n",
        averageOP
    );

    fclose(fPtr);
}

void writeResultToFile(size_t bFOP, size_t hOP) {
    FILE *fPtr = fopen("data/result.txt", "a");

    fprintf(fPtr,
        "\nCritical operations:\n"
        "Brute-force: %d\n"
        "Horspool: %d\n\n"
        "======================================================\n"
        "======================================================\n\n",
        bFOP, hOP
    );

    fclose(fPtr);
}

void readInputFile(char *text, int type) {

    FILE *fPtr = NULL;
    if (type == 1) fPtr = fopen("data/average_input.txt", "r");
    else if (type == 2) fPtr = fopen("data/bf_worst_input.txt", "r");
    else if (type == 3) fPtr = fopen("data/hp_worst_input.txt", "r");

    if (fPtr == NULL)
    {
        exit(-1);
    }
    
    char temp[TEXT_SIZE];

    strcpy(text, "");
    while (!feof(fPtr))
    {
        fgets(temp, TEXT_SIZE, fPtr);
        strcat(text, temp);
    }

    fclose(fPtr);
}

