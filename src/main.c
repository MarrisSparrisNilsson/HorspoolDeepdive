#include "filehandling.h"
#include "algorithm.h"

#define STRING_SIZE 100
#define SIZE 40

static void displayMenu();

int main(int argc, char const *argv[]) {

    char avg_input[TEXT_SIZE];
    char worst_input[TEXT_SIZE];
    readInputFile(avg_input, 1);

    size_t avg_input_size = strlen(avg_input);
    size_t worst_input_size = 0;
    char string[STRING_SIZE], pattern[STRING_SIZE];

    int option, test;

    size_t bFOP, hOP; // Critical operation counters for both algorithms
    int bfIndex, hpIndex = -1;

    while (1) {

        bFOP = 0, hOP = 0;
        
        displayMenu();

        fflush(stdin);
        printf("Select test option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                strcpy(string, "1010100111");
                strcpy(pattern, "100");
            break;
            case 2:
                strcpy(string, "10001111011010110101001101110");
                strcpy(pattern, "00110");
            break;
            case 3:
                strcpy(string, "ETKMINSUVWXOOTM");
                strcpy(pattern, "VWX");
            break;
            case 4:
                strcpy(string, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
                strcpy(pattern, "VWX");
            break;
            case 5:
                strcpy(string, "ALKSDJIFEBEOIHSAWQNOIJASFH");
                strcpy(pattern, "HELLO");
            break;
            case 6:
                strcpy(string, "GEORGE_HAS_A_YELLOW_HAT");
                strcpy(pattern, "YELLOW");
            break;
            case 7:
                fflush(stdin);
                printf("\nEnter a pattern to search for: ");
                gets(pattern);

                bFOP = 0, hOP = 0;

                // Brute-force
                printAverageCaseHeader(avg_input_size, 1, option);
                bfIndex = bruteForceMatching(pattern, avg_input, &bFOP);

                printResult(pattern, bfIndex, bFOP);
                printSummary(bFOP);

                // Horspool
                printAverageCaseHeader(avg_input_size, 2, option);
                hpIndex = horspoolMatching(pattern, avg_input, &hOP);

                printResult(pattern, hpIndex, hOP);
                printSummary(hOP);

            break;
            case 8:
                char *patterns[SIZE] = {
                    "assumenda",
                    "Nesciunt",
                    "praesentium",
                    "est",
                    "pariatur",
                    "recusandae",
                    "provident",
                    "perferendis",
                    "unde",
                    "Minima",
                    "adipisci",
                    "deleniti",
                    "soluta",
                    "labore",
                    "mollitia",
                    "Eos",
                    "hic",
                    "reprehenderit",
                    "Doloribus",
                    "ipsum",
                    "Officiis",
                    "sapiente",
                    "veniam",
                    "Atque",
                    "molestiae",
                    "fuga",
                    "asperiores",
                    "consectetur",
                    "fugiat",
                    "iusto",
                    "deserunt",
                    "necessitatibus",
                    "impedit",
                    "dolor",
                    "Porro",
                    "et",
                    "quis",
                    "voluptas",
                    "Error",
                    "Dignissimos",
                };
                
                // Brute-force
                printAverageCaseHeader(avg_input_size, 1, option);
                size_t i = 0;
                size_t totOP = 0;

                for (; i < SIZE; i++)
                {
                    bFOP = 0;
                    strcpy(pattern, patterns[i]);

                    bfIndex = bruteForceMatching(pattern, avg_input, &bFOP);
                    totOP += bFOP;

                    printResult(pattern, bfIndex, bFOP);
                }
                printSummary(totOP/SIZE);

                // Horspool
                totOP = 0;
                printAverageCaseHeader(avg_input_size, 2, option);
                for (i = 0; i < SIZE; i++)
                {
                    hOP = 0;
                    strcpy(pattern, patterns[i]);

                    hpIndex = horspoolMatching(pattern, avg_input, &hOP);
                    totOP += hOP;

                    printResult(pattern, hpIndex, hOP);
                }
                printSummary(totOP/SIZE);

            break;
            case 9:
                bFOP = 0, hOP = 0;

                // Brute-force
                readInputFile(worst_input, 2);
                worst_input_size = strlen(worst_input);

                strcpy(pattern, "OOA");
                printWorstCaseHeader(worst_input_size, pattern, 1, option);
                bfIndex = bruteForceMatching(pattern, worst_input, &bFOP);

                printResult(pattern, bfIndex, bFOP);
                printSummary(bFOP);

                strcpy(worst_input, "");

                // Horspool
                readInputFile(worst_input, 3);
                worst_input_size = strlen(worst_input);
                strcpy(pattern, "AOO");
                printWorstCaseHeader(worst_input_size, pattern, 2, option);
                hpIndex = horspoolMatching(pattern, worst_input, &hOP);

                printResult(pattern, hpIndex, hOP);
                printSummary(hOP);
            break;
            case 10:
                fflush(stdin);
                printf("\nEnter a string: ");
                gets(string);

                printf("Enter a pattern to search for: ");
                gets(pattern);
            break;
            case 0: exit(-1); break;
            default: puts("Invalid input, please try again."); break;
        }

        if (option < 7 && option > 0)
        {
            printHeader(strlen(string), string, pattern, option);
            printf(
                "\nBrute-force:"
                "\n---------------------"
            );
            bfIndex = bruteForceMatching(pattern, string, &bFOP);
            puts("---------------------");
            
            // Horspool
            printf(
                "\nHorspool:"
                "\n---------------------"
            );
            hpIndex = horspoolMatching(pattern, string, &hOP);
            puts("---------------------");

            if (hpIndex == -1) printf("\n** Pattern '%s' could not be found in %s **\n", pattern, string);
            else printf("\n-- The pattern '%s' was found at index %d of %s --\n", pattern, hpIndex, string);

            writeResultToFile(bFOP, hOP);
        }
    }

    return 0;
}

static void displayMenu() {
    printf(
        // KOM PÅ TEST MED SAMMA STRÄNG MEN OLIKA LÄNGD PÅ PATTERN!
        "\nChoose test:\n"
        "1: 1010100111 - 100\n" // LITE VARIATION, KORT
        "2: 100011110110101101010011011101 - 00110\n" // LITE VARIATION, LÄNGRE
        "3: ETKMINSUVWXOOTM - VWX\n" // VARIATION, KORT
        "4: ABCDEFGHIJKLMNOPQRSTUVWXYZ - VWX\n" // VARIATION, LÄNGRE
        "5: ALKSDJIFEBEOIHSAWQNOIJASFH - HELLO (NO MATCH)\n" // INGEN MATCHNING
        "6: GEORGE_HAS_A_YELLOW_HAT - YELLOW\n"
        "7: Custom AVERAGE CASE\n"
        "8: AVERAGE CASE\n"
        "9: WORST CASE\n"
        "10: Custom input\n"
        "0: Exit\n"
    );
}