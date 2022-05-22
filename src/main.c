#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 20
#define ASCII_SIZE 128

void displayTableMatches(char string[], char pattern[], int tShift);
void shiftTable(int *table, char pattern[]);
int horspoolMatching(char pattern[], char string[], size_t *hOP);
int bruteForceMatching(char pattern[], char string[], size_t *bFOP);
void displayMenu();

int main(int argc, char const *argv[]) {

    // String : JIM_SAW_ME_IN_A_BARBERSHOP
    // Pattern : BARBER

    // // ---------- ASCII ----------
    // printf("\nEnter some number between 1 - 128: ");
    // fflush(stdin);
    // scanf("%d", &option);
    // printf("Character: %c\n", option);
    // // ---------------------------

    char string[STRING_SIZE], pattern[STRING_SIZE];
    int option, test;

    size_t bFOP = 0, hOP = 0; // Critical operation counters for both algorithms
    int matchIndex;

    // char asciiTable[128];
    while (1) {
        
        fflush(stdin);
        printf("\nEnter a string: ");
        scanf("%s", string);

        // 101010101110111010011
        // 1010111011

        printf("Enter a pattern to search for: ");
        scanf("%s", pattern);

        displayMenu();

        printf("Select algorithm: ");
        scanf("%d", &option);

        switch (option) {
            case 1: // Brute-force
                    matchIndex = bruteForceMatching(pattern, string, &bFOP);
                    if (matchIndex == -1) printf("** Pattern %s could not be found in %s **\n", pattern, string);
                    else printf("\n-- The pattern %s was found at index %d of %s --\n", pattern, matchIndex, string);
                    
                break;
            case 2: // Horsppol
                    matchIndex = horspoolMatching(pattern, string, &hOP);
                    if (matchIndex == -1) printf("** Pattern %s could not be found in %s **\n", pattern, string);
                    else printf("\n-- The pattern %s was found at index %d of %s --\n", pattern, matchIndex, string);
                break;
            case -1: exit(-1); break;
            default: puts("Invalid input, please try again."); break;
        }
    }

    return 0;
}

void displayMenu() {
    printf(
        "\nChoose algorithm:\n"
        "1: Brute-force\n"
        "2: Horspools\n"
        "-1: Exit\n"
    );
}

int bruteForceMatching(char pattern[], char string[], size_t *bFOP) {

    int patternLen = strlen(pattern);
    int stringLen = strlen(string);
    int matchingChar;

    int i = 0;
    (*bFOP)++;
    printf("\n%s\n", string);
    printf("%s\n", pattern);
    while (i < stringLen) { // Loop until it reaches the end of the string
        matchingChar = 0;
        int j = i;
        int k = 0;
        (*bFOP)++;
        while (k < patternLen) {
            (*bFOP)++;
            if (pattern[k] == string[j])
                matchingChar++; // Match not found
            j++;
            k++;
        }
        
        if (matchingChar == patternLen) {
            return i;
        }
        else i++;
        printf("\n%s\n", string);
        for (size_t c = 0; c < i; c++) {
            printf(" ");
        }
        printf("%s\n", pattern);
    }
    return -1;
}

void displayTableMatches(char string[], char pattern[], int tShift) {
    printf("\n%s\n", string);
    int m = strlen(pattern);
    for (size_t i = 0; i < tShift - m + 1; i++) {
        printf(" ");
    }
    printf("%s\n", pattern);
}

// Pattern : pattern
// Text : String


// ShiftTable(P[0..m - 1], int asciiTable[]) {
void shiftTable(int *table, char pattern[]) {

    // String : JIM_SAW_ME_IN_A_BARBERSHOP
    // Pattern : BARBER

    // Fills the shift table used by Horspool’s and Boyer-Moore algorithms
    // Input: Pattern P[0..m − 1] and an alphabet of possible characters
    // Output: Table[0..size − 1] indexed by the alphabet’s characters and
    // filled with shift sizes computed by formula (7.1)
    int m = strlen(pattern);
    // int table[128];
    for (size_t i = 0; i <= ASCII_SIZE - 1; i++)
        table[i] = m;
    for (size_t j = 0; j <= m - 2; j++)
        table[(int) pattern[j]] = m - 1 - j;
    // return table;
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
    while (i <= n - 1) {
        k = 0; // number of matched characters
        (*hOP)++;
        while (k <= m - 1 && pattern[m - 1 - k] == string[i - k]) {
            k = k + 1;
            (*hOP)++;
        }
        if (k == m)
            return i - m + 1;
        else i += table[string[i]];
        
        displayTableMatches(string, pattern, i);
    }
    return -1;
}