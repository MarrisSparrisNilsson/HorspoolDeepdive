#include "algorithm.h"

static void displayStringComps(char string[], char pattern[], int tShift);

int bruteForceMatching(char pattern[], char string[], size_t *bFOP) {

    int patternLen = strlen(pattern);
    int stringLen = strlen(string);
    int matchingChar;

    int i = 0;
    // (*bFOP)++;
    printf("\n%s\n", string);
    printf("%s\n", pattern);
    while (i < stringLen) { // Loop until it reaches the end of the string
        matchingChar = 0;
        int j = i;
        int k = 0;
        (*bFOP)++;
        while (k < patternLen && pattern[k] == string[j]) { // Loop pattern characters
            // if (pattern[k] == string[j])
            matchingChar++; // Match not found
            (*bFOP)++;
            j++;
            k++;
        }
        
        if (matchingChar == patternLen)
            return i;
        else i++;
        printf("\n%s\n", string);
        for (size_t c = 0; c < i; c++) {
            printf(" ");
        }
        printf("%s\n", pattern);
    }
    return -1;
}

// ShiftTable(P[0..m - 1], int asciiTable[]) {
void shiftTable(int *table, char pattern[]) {

    // String : JIM_SAW_ME_IN_A_BARBERSHOP
    // Pattern : BARBER

    // Fills the shift table used by Horspool’s and Boyer-Moore algorithms
    // Input: Pattern P[0..m − 1] and an alphabet of possible characters
    // Output: Table[0..size − 1] indexed by the alphabet’s characters and
    // filled with shift sizes computed by formula (7.1)
    int m = strlen(pattern);
    for (size_t i = 0; i <= ASCII_SIZE - 1; i++)
        table[i] = m;
    if (m == 1) // When pattern only constist of one character
        table[(int) pattern[0]] = 0;
    else 
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

    // P[0..m − 1]
    shiftTable(table, pattern); // generate Table of shifts
    int i = m - 1; // position of the pattern’s right end
    printf("\n%s\n", string);
    printf("%s\n", pattern);
    while (i <= n - 1) { // Loop until it reaches the end of the string
        k = 0; // number of matched characters
        (*hOP)++;
        // Loop pattern characters
        while (k <= m - 1 && pattern[m - 1 - k] == string[i - k]) { 
            k = k + 1;
            (*hOP)++;
        }
        // If the number of character matches
        // is the same as the pattern length
        if (k == m) 
            return i - m + 1; // Index where a match was found
        else i += table[string[i]];
        
        displayStringComps(string, pattern, i);
    }
    return -1;
}

static void displayStringComps(char string[], char pattern[], int tShift) {
    printf("\n%s\n", string);
    int m = strlen(pattern);
    for (size_t i = 0; i < tShift - m + 1; i++) {
        printf(" ");
    }
    printf("%s\n", pattern);
}