#include "stdio.h"

#define SECTION_SIZE 4

void initSection(char section[][SECTION_SIZE], int size, char initVal) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            section[i][j] = initVal;
        }
    }
}

void printRow(char row[], int size) {
    for (int i = 0; i < SECTION_SIZE; i++) {
        printf("%c ", row[i]);
    }
    printf("\n");
}

void printSection(int sectionIndex, char section[], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            setbuf(stdout, 0);
            printf("(%d %d %d) ", sectionIndex, i, j);
        }
        for (int k = i*size; k < size*(i+1); k++) {
            setbuf(stdout, 0);
            printf("%c ", section[k]);
        }
        printf("\n");
    }
}

// return the char of the winner. return '0' if tie (only possible output is tie, X win or O win)
char determineRowWinner(char section[][SECTION_SIZE], int size) {
    char winner = '0';
    for (int i = 0; i < size; ++i) {
        char prev = section[i][0];
        for (int j = 1; j < size; ++j) {
            char cur = section[i][j];
            if (cur != prev) {
                return '0';
            }
            else {
                winner = cur;
            }
            prev = cur;
        }
    }
    return winner;
}

// return the char of the winner. return '0' if tie (only possible output is tie, X win or O win)
char determineColWinner(char section[][SECTION_SIZE], int size) {
    char winner = '0';
    for (int i = 0; i < size; ++i) {
        char prev = section[0][i];
        for (int j = 1; j < size; ++j) {
            char cur = section[j][i];
            if (cur != prev) {
                return '0';
            }
            else {
                winner = cur;
            }
            prev = cur;
        }
    }
    return winner;
}


// return the char of the winner. return '0' if tie (only possible output is tie, X win or O win)
char determineDiagWinner(char section[][SECTION_SIZE], int size) {
    char winner = '0';
    for (int i = 1; i < size; ++i) {
        char prev = section[i - 1][i - 1];
        char cur = section[i][i];
        if (cur != prev) {
            return '0';
        }
        else {
            winner = cur;
        }
    }

    return winner;
}


int determineWinner(int size,
                    char section0[][SECTION_SIZE],
                    char section1[][SECTION_SIZE],
                    char section2[][SECTION_SIZE],
                    char section3[][SECTION_SIZE]) {
    const char TIE = '0';

    char rowWinner0 = determineRowWinner(section0, size);
    char rowWinner1 = determineRowWinner(section1, size);
    char rowWinner2 = determineRowWinner(section2, size);
    char rowWinner3 = determineRowWinner(section3, size);

    char colWinner0 = determineColWinner(section0, size);
    char colWinner1 = determineColWinner(section1, size);
    char colWinner2 = determineColWinner(section2, size);
    char colWinner3 = determineColWinner(section3, size);

    char diagWinner0 = determineDiagWinner(section0, size);
    char diagWinner1 = determineDiagWinner(section1, size);
    char diagWinner2 = determineDiagWinner(section2, size);
    char diagWinner3 = determineDiagWinner(section3, size);

    if (section0[0][0] == section1[1][1] && section0[0][0] == section2[2][2] && section0[0][0] == section3[3][3]) {
        if (section0[0][0] == 'X' || section0[0][0] == 'O') {
            return section0[0][0];
        }
    }

//    char multiRowWinner0 = determineMultiRowWinner(section0, size);
//    char multiRowWinner1 = determineMultiRowWinner(section1, size);
//    char multiRowWinner2 = determineMultiRowWinner(section2, size);
//    char multiRowWinner3 = determineMultiRowWinner(section3, size);
//
//    char multiColWinner0 = determineMultiColWinner(section0, size);
//    char multiColWinner1 = determineMultiColWinner(section1, size);
//    char multiColWinner2 = determineMultiColWinner(section2, size);
//    char multiColWinner3 = determineMultiColWinner(section3, size);
//
//    char multiDiagWinner0 = determineMultiDiagWinner(section0, size);
//    char multiDiagWinner1 = determineMultiDiagWinner(section1, size);
//    char multiDiagWinner2 = determineMultiDiagWinner(section2, size);
//    char multiDiagWinner3 = determineMultiDiagWinner(section3, size);



    switch (rowWinner0) {
        case 'X':
        case 'O':
            return rowWinner0;
        default:
            break;
    }
    switch (rowWinner1) {
        case 'X':
        case 'O':
            return rowWinner1;
        default:
            break;
    }
    switch (rowWinner2) {
        case 'X':
        case 'O':
            return rowWinner2;
        default:
            break;
    }
    switch (rowWinner3) {
        case 'X':
        case 'O':
            return rowWinner3;
        default:
            break;
    }

    switch (colWinner0) {
        case 'X':
        case 'O':
            return colWinner0;
        default:
            break;
    }
    switch (colWinner1) {
        case 'X':
        case 'O':
            return colWinner1;
        default:
            break;
    }
    switch (colWinner2) {
        case 'X':
        case 'O':
            return colWinner2;
        default:
            break;
    }
    switch (colWinner3) {
        case 'X':
        case 'O':
            return colWinner3;
        default:
            break;
    }

    switch (diagWinner0) {
        case 'X':
        case 'O':
            return diagWinner0;
        default:
            break;
    }
    switch (diagWinner1) {
        case 'X':
        case 'O':
            return diagWinner1;
        default:
            break;
    }
    switch (diagWinner2) {
        case 'X':
        case 'O':
            return diagWinner2;
        default:
            break;
    }
    switch (diagWinner3) {
        case 'X':
        case 'O':
            return diagWinner3;
        default:
            break;
    }

    return TIE;
}

// game() will return 0 if there is a winner or a tie. It will return a 1 if there was an error

int game() {
    const char EMPTY_SPOT = '*';
    char winner = 'q';
    char section0 [SECTION_SIZE][SECTION_SIZE];
    char section1 [SECTION_SIZE][SECTION_SIZE];
    char section2 [SECTION_SIZE][SECTION_SIZE];
    char section3 [SECTION_SIZE][SECTION_SIZE];
    enum pos {
        section = 0,
        row = 1,
        column = 2,
    };

    initSection(section0, SECTION_SIZE, EMPTY_SPOT);
    initSection(section1, SECTION_SIZE, EMPTY_SPOT);
    initSection(section2, SECTION_SIZE, EMPTY_SPOT);
    initSection(section3, SECTION_SIZE, EMPTY_SPOT);

    char input = getchar();
    int index = 0;
    int isXturn = 1;
    while (input == '\n' || input == ' ') {
        input = getchar();
    }
    while (winner == 'q') { //!(winner || isTie)
        int chosenSection = 0, chosenRow = 0, chosenColumn = 0;
        while (input != '\n') {
            switch (index % 3) {
                case section: {
                    //todo: get the switch statements into a function or just convert from char to int (but remember to check validity first!)
                    switch (input) {
                        case '0':
                            chosenSection = 0;
                            break;
                        case '1':
                            chosenSection = 1;
                            break;
                        case '2':
                            chosenSection = 2;
                            break;
                        case '3':
                            chosenSection = 3;
                            break;
                        default:
                            return 1;
                    }
                    break;
                }
                case row: {
                    switch (input) {
                        case '0':
                            chosenRow = 0;
                            break;
                        case '1':
                            chosenRow = 1;
                            break;
                        case '2':
                            chosenRow = 2;
                            break;
                        case '3':
                            chosenRow = 3;
                            break;
                        default:
                            return 1;
                    }
                    break;
                }
                case column: {
                    switch (input) {
                        case '0':
                            chosenColumn = 0;
                            break;
                        case '1':
                            chosenColumn = 1;
                            break;
                        case '2':
                            chosenColumn = 2;
                            break;
                        case '3':
                            chosenColumn = 3;
                            break;
                        default:
                            return 1;
                    }

                    if (chosenSection != -1 && chosenRow != -1 && chosenColumn != -1) { //we have all the info we need!
                        switch (chosenSection) {
                            case 0: //todo: use a damn function
                                if (section0[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section0[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }

                                return 1;
                            case 1:
                                if (section1[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section1[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }
                                return 1;
                            case 2:
                                if (section2[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section2[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }
                                return 1;
                            case 3:
                                if (section3[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section3[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }
                                return 1;
                        }
                        isXturn = !isXturn;
                        break;
                    }
                }
                default: {
                    return 1;
                }
            }

            int isSpace = 0;
            do {
                input = getchar();
                if (input != ' ' && input != '\n' && !isSpace) {
                    return 1;
                }
                isSpace = 1;
            } while (input == ' ');
            ++index;
        }

        winner = determineWinner(SECTION_SIZE, section0, section1, section2, section3);
        switch (winner) {
            case 'X':
                printf("X is the winner.\n");
                break;
            case 'O':
                printf("O is the winner.\n");
                break;
            case '0':
                printf("Tie.\n");
                break;
            default:
                printf("Tie.\n");
                break;
        }

        printSection(0, section0, SECTION_SIZE);
        printf("\n");
        printSection(1, section1, SECTION_SIZE);
        printf("\n");
        printSection(2, section2, SECTION_SIZE);
        printf("\n");
        printSection(3, section3, SECTION_SIZE);
        printf("\n");
    }

    return 0;
}


int main () {
    printf("Would you like to start? (y/n)\n");
    while(1) {
        char choice;
        scanf("%c", &choice);
        switch (choice) {
            case 'y':
                printf("Please enter your game sequence.\n");
                if (game()) {
                    printf("Input incorrect.\n");
                }

                printf("Would you like to continue? (y/n)\n");
                continue;
            case 'n':
                printf("YEET\n");
                return 0;
            default:
                printf("YEET\n");
                return 0;
        }
    } // end of while loop
}