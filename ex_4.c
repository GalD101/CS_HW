/******************************************
*Student name: Gal Dali
*Student ID: 322558297
*Exercise name: ex3
******************************************/

#include "stdio.h"

#define SECTION_SIZE 4

/************************************************************************
* function name: initSection *
* The Input: char section[][SECTION_SIZE], int size, char initVal *
* The output: *
* The Function operation: initialize a 2d char array with an initial value *
*************************************************************************/
void initBoard(char board[][SECTION_SIZE][SECTION_SIZE], int size, char
initVal) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size * (i + 1); k++) {
                board[i][j][k] = initVal;
            }
        }
    }
}

//void printRow(char row[], int size) {
//    for (int i = 0; i < size; i++) {
//        printf("%c ", row[i]);
//    }
//    printf("\n");
//}

void printBoard(char section[][SECTION_SIZE][SECTION_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                printf("(%d %d %d) ", i, j, k);
            }
            for (int k = 0; k < size; ++k) {
                printf("%c ", section[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

// return the char of the winner. return '_' if tie (only possible output is tie, X win or O win)
char determineRowWinner(char section[][SECTION_SIZE], int size) {
    char winner = 'z';
    for (int i = 0; i < size; ++i) {
        char prev = section[i][0];
        for (int j = 1; j < size; ++j) {
            char cur = section[i][j];
            if (cur != prev) {
                return '_';
            } else {
                winner = cur;
            }
            prev = cur;
        }
    }
    return winner;
}

// return the char of the winner. return '_' if tie (only possible output is tie, X win or O win)
char determineColWinner(char section[][SECTION_SIZE], int size) {
    char winner = 'z';
    for (int i = 0; i < size; ++i) {
        char prev = section[0][i];
        for (int j = 1; j < size; ++j) {
            char cur = section[j][i];
            if (cur != prev) {
                return '_';
            } else {
                winner = cur;
            }
            prev = cur;
        }
    }
    return winner;
}


// return the char of the winner. return '_' if tie (only possible output is tie, X win or O win)
char determineDiagWinner(char section[][SECTION_SIZE], int size) {
    char winner = 'z';
    for (int i = 1; i < size; ++i) {
        char prev = section[i - 1][i - 1];
        char cur = section[i][i];
        if (cur != prev) {
            return '_';
        } else {
            winner = cur;
        }
    }

    return winner;
}


int determineWinnerBoard(int size, char board[][SECTION_SIZE][SECTION_SIZE],
                         int isGameOver) {
    const char TIE = '_';
    const char NO_WINNER = 'z';

    for (int i = 0; i < size; ++i) {
        char rowWinner = determineRowWinner(board[i], size);
        if (rowWinner == 'X' || rowWinner == 'O') {
            return rowWinner;
        }
    }

    for (int i = 0; i < size; ++i) {
        char colWinner = determineColWinner(board[i], size);
        if (colWinner == 'X' || colWinner == 'O') {
            return colWinner;
        }
    }

    for (int i = 0; i < size; ++i) {
        char diagWinner = determineDiagWinner(board[i], size);
        if (diagWinner == 'X' || diagWinner == 'O') {
            return diagWinner;
        }
    }

    if (board[0][0][0] == board[1][1][1] && board[0][0][0] == board[2][2][2] &&
        board[0][0][0] == board[3][3][3]) {
        if (board[0][0][0] == 'X' || board[0][0][0] == 'O') {
            return board[0][0][0];
        }
    }
    return isGameOver ? TIE : NO_WINNER;
}


int determineWinner(int size,
                    char section0[][SECTION_SIZE],
                    char section1[][SECTION_SIZE],
                    char section2[][SECTION_SIZE],
                    char section3[][SECTION_SIZE]) {
    const char TIE = '_';

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

    if (section0[0][0] == section1[1][1] && section0[0][0] == section2[2][2] &&
        section0[0][0] == section3[3][3]) {
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


int isValidInput(char input) {
    return input == '0' || input == '1' || input == '2' || input == '3';
}


// todo: check how to define a char like '*' in a preprocessor
int updateSection(char section[][SECTION_SIZE], int row, int col, int isXturn,
                  const char EMPTY_SPOT) {
    int isSpotEmpty = section[row][col] == EMPTY_SPOT;
    if (isSpotEmpty) {
        section[row][col] = isXturn ? 'X' : 'O';
    }

    return !isSpotEmpty;
}

int updateBoard(char board[][SECTION_SIZE][SECTION_SIZE],int section,
                int row, int col, int isXturn, const char EMPTY_SPOT) {
    int isSpotEmpty = board[section][row][col] == EMPTY_SPOT;
    if (isSpotEmpty) {
        board[section][row][col] = isXturn ? 'X' : 'O';
    }

    return !isSpotEmpty;
}

// game() will return 0 if there is a winner or a tie. It will return a 1 if there was an error
int game() {
    const char EMPTY_SPOT = '*';
    char winner = 'z';
    char board[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE];
    enum pos {
        section = 0,
        row = 1,
        column = 2,
    };

    initBoard(board, SECTION_SIZE, EMPTY_SPOT);

    char input = getchar();
    int index = 0;
    int isXturn = 1;
    while (input == '\n' || input == ' ') {
        input = getchar();
    }
    while (winner == 'z') { //!(winner || isTie)
        int chosenSection = 0, chosenRow = 0, chosenColumn = 0;
        while (input != '\n' && winner == 'z') {
            if (!isValidInput(input)) {
                return 1;
            }
            int integerInput = input - '0';
            switch (index % 3) {
                case section: {
                    chosenSection = integerInput;
                    break;
                }
                case row: {
                    chosenRow = integerInput;
                    break;
                }
                case column: {
                    chosenColumn = integerInput;

                    if (chosenSection != -1 && chosenRow != -1 &&
                        chosenColumn != -1) {
                        if (updateBoard(board, chosenSection,
                                        chosenRow, chosenColumn, isXturn,
                                        EMPTY_SPOT)) {
                            return 1;
                        }
                        winner = determineWinnerBoard(SECTION_SIZE, board, 0);
                        isXturn = !isXturn;
                    }
                    break;
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

        if (index < 2) {
            return 1;
        }
        if (winner == 'z') {
            winner = determineWinnerBoard(SECTION_SIZE, board, 1);
        }
        switch (winner) {
            case 'X':
                printf("X is the winner.\n");
                break;
            case 'O':
                printf("O is the winner.\n");
                break;
            case '_':
            default:
                printf("Tie.\n");
                break;
        }

        printBoard(board, SECTION_SIZE);
    }

    return 0;
}


int main() {
//    char a [SECTION_SIZE][SECTION_SIZE][SECTION_SIZE];
//
//    initBoard(a, SECTION_SIZE, '*');
//    printBoard(a, SECTION_SIZE);
    printf("Would you like to start? (y/n)\n");
    while (1) {
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
                break;
        }
    } // end of while loop
}