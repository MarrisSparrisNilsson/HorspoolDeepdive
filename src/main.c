#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filehandling.h"
#include "algorithm.h"

#define STRING_SIZE 30

static void displayMenu();

int main(int argc, char const *argv[]) {

    // String : JIM_SAW_ME_IN_A_BARBERSHOP
    // Pattern : BARBER

    char string[STRING_SIZE], pattern[STRING_SIZE];
    int option, test;

    size_t bFOP, hOP; // Critical operation counters for both algorithms
    int matchIndex;

    while (1) {
        // 101010101110111010011
        // 1010111011

        bFOP = 0, hOP = 0;
        
        displayMenu();

        fflush(stdin);
        printf("Select test option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                strcpy(string, "Horspool");
                strcpy(pattern, "pool");
            break;
            case 2:
                strcpy(string, "1010100111");
                strcpy(pattern, "100");
            break;
            case 3:
                strcpy(string, "10001111011010110101001101110");
                strcpy(pattern, "00110");
            break;
            case 4:
                strcpy(string, "ETKMINSUVWXOOTM");
                strcpy(pattern, "VWX");
            break;
            case 5:
                strcpy(string, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
                strcpy(pattern, "VWX");
            break;
            case 6:
                strcpy(string, "ALKSDJIFEBEOIHSAWQNOIJASFH");
                strcpy(pattern, "HELLO");
            break;
            case 7:
                strcpy(string, "GEORGE_HAS_A_YELLOW_HAT");
                strcpy(pattern, "YELLOW");
            break;
            case 8:
                strcpy(string, "11111111111111111101");
                strcpy(pattern, "0");
            break;
            case 9:
                strcpy(string, "11111111111111111101");
                strcpy(pattern, "01");
            break;
            case 10:
                strcpy(string, "ETKMINSUVWXOOTM");
                strcpy(pattern, "VWXOOTM");
            break;
            case 15: 
                printf("\nEnter a string: ");
                scanf("%s", string);

                printf("Enter a pattern to search for: ");
                scanf("%s", pattern);
            break;
            case 0: exit(-1); break;
            default: puts("Invalid input, please try again."); break;
        }
        printHeader(string, pattern);
        printf(
            "\nBrute-force:"
            "\n---------------------"
        );
        matchIndex = bruteForceMatching(pattern, string, &bFOP);
        puts("---------------------");
        
        // Horspool
         printf(
            "\nHorspool:"
            "\n---------------------"
        );
        horspoolMatching(pattern, string, &hOP);
        puts("---------------------");
        if (matchIndex == -1) printf("** Pattern %s could not be found in %s **\n", pattern, string);
        else printf("\n-- The pattern %s was found at index %d of %s --\n", pattern, matchIndex, string);

        writeResultToFile(bFOP, hOP);
    }

    return 0;
}

static void displayMenu() {
    printf(
        // KOM PÅ TEST MED SAMMA STRÄNG MEN OLIKA LÄNGD PÅ PATTERN!
        "\nChoose test:\n"
        "1: Horspool - pool\n"
        "2: 1010100111 - 100\n" // LITE VARIATION, KORT
        "3: 100011110110101101010011011101 - 00110\n" // LITE VARIATION, LÅNGT
        "4: ETKMINSUVWXOOTM - VWX\n" // VARIATION, KORT
        "5: ABCDEFGHIJKLMNOPQRSTUVWXYZ - VWX\n" // VARIATION, LÅNGT
        "6: ALKSDJIFEBEOIHSAWQNOIJASFH - HELLO\n" // INGEN MATCHNING
        "7: GEORGE_HAS_A_YELLOW_HAT - YELLOW\n"
        "8: 11111111111111111101 - 0\n"
        "9: 11111111111111111101 - 01\n"
        "10: ETKMINSUVWXOOTM - VMXOOTM\n"

        "10: 11111111111111111101 - 01\n"
        "11: YELLOW - YELLOW\n"
        "11: BELLOW - YELLOW\n"
        "3: 100011110110101101010011011101 - 100011110110101101010011011101\n" // LITE VARIATION, LÅNGT
        "15: Custom Choice\n"
        "0: Exit\n"
    );
}

// Pattern : pattern
// Text : String