/******************************************
*Student name: Gal Dali
*Student ID: 322558297
*Exercise name: ex3
******************************************/

#include "stdio.h"

#define SECTION_SIZE 4

const char NO_WINNER  = ' ';
const char TIE        = '_';
const char EMPTY_SPOT = '*';

/************************************************************************
* function name: initSection *
* The Input: char section[][SECTION_SIZE], int size, char initVal *
* The output: no output *
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
    char winner = NO_WINNER;
    for (int i = 0; i < size; ++i) {
        char prev = section[i][0];
        for (int j = 1; j < size; ++j) {
            char cur = section[i][j];
            if (cur != prev) {
                return TIE;
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
    char winner = NO_WINNER;
    for (int i = 0; i < size; ++i) {
        char prev = section[0][i];
        for (int j = 1; j < size; ++j) {
            char cur = section[j][i];
            if (cur != prev) {
                return TIE;
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
    char winner = NO_WINNER;
    for (int i = 1; i < size; ++i) {
        char prev = section[i - 1][i - 1];
        char cur = section[i][i];
        if (cur != prev) {
            return TIE;
        } else {
            winner = cur;
        }
    }

    return winner;
}


int determineWinnerBoard(int size, char board[][SECTION_SIZE][SECTION_SIZE],
                         int isGameOver) {
    for (int i = 0; i < size; ++i) {
        char rowWinner = determineRowWinner(board[i], size);
        if (rowWinner == 'X' || rowWinner == 'O') {
            return rowWinner;
        }
        char colWinner = determineColWinner(board[i], size);
        if (colWinner == 'X' || colWinner == 'O') {
            return colWinner;
        }
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

int isValidInput(char input) {
    return input == '0' || input == '1' || input == '2' || input == '3';
}

int updateBoard(char board[][SECTION_SIZE][SECTION_SIZE], int section,
                int row, int col, int isXturn, const char EMPTY_SPOT) {
    int isSpotEmpty = board[section][row][col] == EMPTY_SPOT;
    if (isSpotEmpty) {
        board[section][row][col] = isXturn ? 'X' : 'O';
    }

    return !isSpotEmpty;
}

// game() will return 0 if there is a winner or a tie. It will return a 1 if there was an error
int game() {
    char winner = NO_WINNER;
    char board[SECTION_SIZE][SECTION_SIZE][SECTION_SIZE];
    enum coordinates {
        section = 0,
        row = 1,
        column = 2,
    };

    initBoard(board, SECTION_SIZE, EMPTY_SPOT);

    char input = getchar();
    int index = 0;
    int isXturn = 1;
    while (input == '\n') {
        input = getchar();
    }

    int chosenSection = 0, chosenRow = 0, chosenColumn = 0;
    while (input != '\n' && winner == NO_WINNER) {
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

                if (updateBoard(board, chosenSection,
                                chosenRow, chosenColumn, isXturn,
                                EMPTY_SPOT)) {
                    return 1;
                }
                winner = determineWinnerBoard(SECTION_SIZE, board, 0);
                isXturn = !isXturn;
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
    if (winner == NO_WINNER) {
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

    while (input != '\n') {
        input = getchar();
    }
    return 0;
}


int main() {
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
            default:
                printf("YEET\n");
                return 0;
                break;
        }
    } // end of while loop
}
