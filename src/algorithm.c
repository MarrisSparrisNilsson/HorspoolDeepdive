#include "algorithm.h"

static void displayStringCompsBF(char string[], char pattern[], int tShift);
static void displayStringCompsHP(char string[], char pattern[], int tShift);

int bruteForceMatching(char pattern[], char string[], size_t *bFOP) {

    int m = strlen(pattern);
    int n = strlen(string);
    

    for (int i = 0; i <= n - m; i++) { // Loop until it reaches the end of the string
        if (n < 100)
            displayStringCompsBF(string, pattern, i);
        int j = 0;
        (*bFOP)++;
        // Loop pattern characters while matching
        while (j < m && pattern[j] == string[i + j]) { // *Critical operation*
            j = j + 1;
            (*bFOP)++;
        }
        
        if (j == m) // Match was found
            return i;
    }
    return -1;
}

void shiftTable(int *table, char pattern[]) {
    // Fills the shift table used by Horspool’s and Boyer-Moore algorithms
    // Input: Pattern P[0..m − 1] and an alphabet of possible characters
    // Output: Table[0..size − 1] indexed by the alphabet’s characters and
    // filled with shift sizes computed by formula (7.1)
    int m = strlen(pattern);
    for (size_t i = 0; i <= ASCII_SIZE - 1; i++)
        table[i] = m;
    if (m != 1) // When pattern only constist of one character 
        for (size_t j = 0; j <= m - 2; j++)
            table[(int) pattern[j]] = m - 1 - j;
}

int horspoolMatching(char pattern[], char string[], size_t *hOP) {

    // Implements Horspool’s algorithm for string matching
    // Input: Pattern P[0..m − 1] and text T [0..n − 1]
    // Output: The index of the left end of the first matching substring
    // or −1 if there are no matches
    int table[ASCII_SIZE];
    int m = strlen(pattern);
    int n = strlen(string);
    int k; // Character match counter

    shiftTable(table, pattern); // generate Table of shifts
    int i = m - 1; // index of the pattern’s right end

    while (i <= n - 1) { // Loop until it reaches the end of the string
        if (n < 100)
            displayStringCompsHP(string, pattern, i);
        k = 0; // number of matched characters
        (*hOP)++;
        // Loop pattern characters while matching
        while (k <= m - 1 && pattern[m - 1 - k] == string[i - k]) { // *Critical operation*
            k = k + 1;
            (*hOP)++;
        }
        // If match was found
        if (k == m) 
            return i - m + 1; // Index where a match was found
        else i += table[string[i]];
    }
    return -1;
}

static void displayStringCompsBF(char string[], char pattern[], int tShift) {
    printf("\n%s\n", string);
    for (size_t c = 0; c < tShift; c++) {
        printf(" ");
    }
    printf("%s\n", pattern);
}

static void displayStringCompsHP(char string[], char pattern[], int tShift) {
    printf("\n%s\n", string);
    int m = strlen(pattern);
    for (size_t i = 0; i < tShift - m + 1; i++) {
        printf(" ");
    }
    printf("%s\n", pattern);
}