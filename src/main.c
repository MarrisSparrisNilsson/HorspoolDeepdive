#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 20
#define ASCII_SIZE 128

void displayTableMatches(char string[], char queryString[], int tShift);
void shiftTable(int *table, char queryString[]);
int horspoolMatching(char queryString[], char string[]);
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

    char string[STRING_SIZE], queryString[STRING_SIZE];
    int option;

    // char asciiTable[128];
    while (1) {
        
        fflush(stdin);
        printf("\nEnter a string: ");
        scanf("%s", string);

        // 101010101110111010011
        // 1010111011

        printf("Enter a string to search for: ");
        scanf("%s", queryString);

        displayMenu();

        printf("Select algorithm: ");
        scanf("%d", &option);

        switch (option) {
            case 1: // Brute-force
                    
                break;
            case 2: // Horsppol
                    int matchIndex = horspoolMatching(queryString, string);
                    if (matchIndex == -1) printf("** Pattern %s could not be found in %s **\n", queryString, string);
                    else printf("\n-- The pattern %s was found at index %d of %s --\n", queryString, matchIndex, string);
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

int bruteForceStrMatching() {

    // while (/* i + queryString_size < string_size */) {

    //     if (/* i + queryString_size > string_size*/) {
    //         return 0; // Match not found
    //     }
    // }
    // if (/* found */) {
    //     return 1;
    // }
    // else return 0;
}

void displayTableMatches(char string[], char queryString[], int tShift) {
    printf("\n%s\n", string);
    int m = strlen(queryString);
    for (size_t i = 0; i < tShift - m + 1; i++) {
        printf(" ");
    }
    printf("%s\n", queryString);
}

// Pattern : queryString
// Text : String


// ShiftTable(P[0..m - 1], int asciiTable[]) {
void shiftTable(int *table, char queryString[]) {

    // String : JIM_SAW_ME_IN_A_BARBERSHOP
    // Pattern : BARBER

    // Fills the shift table used by Horspool’s and Boyer-Moore algorithms
    // Input: Pattern P[0..m − 1] and an alphabet of possible characters
    // Output: Table[0..size − 1] indexed by the alphabet’s characters and
    // filled with shift sizes computed by formula (7.1)
    int m = strlen(queryString);
    // int table[128];
    for (size_t i = 0; i <= ASCII_SIZE - 1; i++)
        table[i] = m;
    for (size_t j = 0; j <= m - 2; j++)
        table[(int) queryString[j]] = m - 1 - j;
    // return table;
}


int horspoolMatching(char queryString[], char string[]) {

    // Implements Horspool’s algorithm for string matching
    // Input: Pattern P[0..m − 1] and text T [0..n − 1]
    // Output: The index of the left end of the first matching substring
    // or −1 if there are no matches
    int table[ASCII_SIZE];
    int m = strlen(queryString);
    int n = strlen(string);
    int k; // Character match counter

    // P[0..m − 1]
    shiftTable(table, queryString); // generate Table of shifts
    int i = m - 1; // position of the pattern’s right end
    printf("\n%s\n", string);
    printf("%s\n", queryString);
    while (i <= n - 1) {
        k = 0; // number of matched characters
        while (k <= m - 1 && queryString[m - 1 - k] == string[i - k]) {
            k = k + 1;
        }
        if (k == m)
            return i - m + 1;
        else i += table[string[i]];
        
        displayTableMatches(string, queryString, i);
    }
    return -1;
}