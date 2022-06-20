#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filehandling.h"
#include "algorithm.h"

#define STRING_SIZE 50

static void displayMenu();
static void displayTestOptions();

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
            case 1:
                // Brute-force
                printHeader(string, pattern);
                matchIndex = bruteForceMatching(pattern, string, &bFOP);
                if (matchIndex == -1) printf("** Pattern %s could not be found in %s **\n", pattern, string);
                else printf("\n-- The pattern %s was found at index %d of %s --\n", pattern, matchIndex, string);
                
                // Horsppol
                matchIndex = horspoolMatching(pattern, string, &hOP);
                if (matchIndex == -1) printf("** Pattern %s could not be found in %s **\n", pattern, string);
                else printf("\n-- The pattern %s was found at index %d of %s --\n", pattern, matchIndex, string);

                writeResultToFile(bFOP, hOP);

            break;
            case 0: exit(-1); break;
            default: puts("Invalid input, please try again."); break;
        }
    }

    return 0;
}

static void displayMenu() {
    printf(
        "\nChoose option:\n"
        "1: Run Horspool test\n"
        "0: Exit\n"
    );
}

static void displayTestOptions() {
    printf(
        "\nChoose test:\n"
        "1: Horspool - pool\n"
        "2: \n"
    );
}

// Pattern : pattern
// Text : String