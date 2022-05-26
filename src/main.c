#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRING_SIZE 20

void displayTableMatches(char string[], char pattern[], int tShift);

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