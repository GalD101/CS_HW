/******************************************
*Student name: Gal Dali
*Student ID: 322558297
*Exercise name: ex3
******************************************/

#include "stdio.h"

#define SECTION_SIZE 4

// Define global constants
const char NO_WINNER = ' ';
const char TIE = '_';
const char EMPTY_SPOT = '*';

/************************************************************************
* function name: initBoard *
* The Input: char board[][SECTION_SIZE][SECTION_SIZE], int size, char initVal *
* The output: no output *
* The Function operation: initialize a 3d char array with an initial value *
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

/************************************************************************
* function name: printBoard *
* The Input: char board[][SECTION_SIZE][SECTION_SIZE], int size *
* The output: print the given board in a specific format *
* The Function operation: loops over the board and print it in a specific
 * format*
*************************************************************************/
void printBoard(char board[][SECTION_SIZE][SECTION_SIZE], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                printf("(%d %d %d) ", i, j, k);
            }
            for (int k = 0; k < size; ++k) {
                printf("%c ", board[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

/************************************************************************
* function name: determineRowWinner *
* The Input: char section[][SECTION_SIZE], int size *
* The output: return the char of the row winner. return '_' (NO_WINNER) if
 * no winner was found *
* The Function operation: loop over the given section and determine if there
 * is a row winner and who is the row winner *
*************************************************************************/
char determineRowWinner(char section[][SECTION_SIZE], int size) {
    char winner = NO_WINNER;
    char prev, cur;

    for (int i = 0; i < size; ++i) {
        prev = section[i][0];
        for (int j = 1; j < size; ++j) {
            cur = section[i][j];
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

/************************************************************************
* function name: determineColWinner *
* The Input: char section[][SECTION_SIZE], int size *
* The output: return the char of the col winner. return '_' (NO_WINNER) if
 * no winner was found *
* The Function operation: loop over the given section and determine if there
 * is a col winner and who is the col winner *
*************************************************************************/
char determineColWinner(char section[][SECTION_SIZE], int size) {
    char winner = NO_WINNER;
    char prev, cur;

    for (int i = 0; i < size; ++i) {
        prev = section[0][i];
        for (int j = 1; j < size; ++j) {
            cur = section[j][i];
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

/************************************************************************
* function name: determineMultiColWinner *
* The Input: char board[][SECTION_SIZE][SECTION_SIZE], int size *
* The output: return the char of the multiCol winner. return '_' (NO_WINNER) if
 * no winner was found *
* The Function operation: loop over the given section and determine if there
 * is a multiCol winner and who is the multiColo winner *
*************************************************************************/
char determineMultiColWinner(char board[][SECTION_SIZE][SECTION_SIZE], int
size) {
    char cur = NO_WINNER;

    for (int i = 0; i < size; ++i) {
        cur = board[0][0][i];
        if (cur == board[1][1][i] && cur == board[2][2][i] &&
            cur == board[3][3][i]) {
            if (cur == 'X' || cur == 'O') {
                return cur;
            }
        }
    }

    return NO_WINNER;
}

/************************************************************************
* function name: determineDiagWinner *
* The Input: char section[][SECTION_SIZE], int size *
* The output: return the char of the diag winner. return '_' (NO_WINNER) if
 * no winner was found *
* The Function operation: loop over the given section and determine if there
 * is a diag winner and who is the diag winner *
*************************************************************************/
char determineDiagWinner(char section[][SECTION_SIZE], int size) {
    char winner = NO_WINNER;
    char prev;
    char cur;
    for (int i = 1; i < size; ++i) {
        prev = section[i - 1][i - 1];
        cur = section[i][i];
        if (cur != prev) {
            return TIE;
        } else {
            winner = cur;
        }
    }

    return winner;
}

/************************************************************************
* function name: determineWinnerBoard *
* The Input: char board[][SECTION_SIZE][SECTION_SIZE],
 * int size, int isGameOver *
* The output: returns the winning character or _ when tie. If there is no
 * winner and the game is not over, return the NO_WINNER sign *
* The Function operation: loop over the board and look for a winning position.
 * If there is a winner, return the winner. If there is no winner and the game
 * is over, return the TIE sign., if the game is not over, return
 * the NO_WINNER sign*
*************************************************************************/
char determineWinnerBoard(char board[][SECTION_SIZE][SECTION_SIZE], int size,
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

    char multiColWinner = determineMultiColWinner(board, size);
    if (multiColWinner == 'X' || multiColWinner == 'O') {
        return multiColWinner;
    }

    if (board[0][0][0] == board[1][1][1] && board[0][0][0] == board[2][2][2] &&
        board[0][0][0] == board[3][3][3]) {
        if (board[0][0][0] == 'X' || board[0][0][0] == 'O') {
            return board[0][0][0];
        }
    }

    if (board[0][0][3] == board[1][1][2] && board[0][0][3] == board[2][2][1] &&
        board[0][0][3] == board[3][3][0]) {
        if (board[0][0][3] == 'X' || board[0][0][3] == 'O') {
            return board[0][0][3];
        }
    }

    return isGameOver ? TIE : NO_WINNER;
}

/************************************************************************
* function name: isValidInput *
* The Input: char input *
* The output: return whether or not the given input is valid *
* The Function operation: check if the input is meeting the requirements *
*************************************************************************/
int isValidInput(char input) {
    return input == '0' || input == '1' || input == '2' || input == '3';
}

/************************************************************************
* function name: updateBoard *
* The Input: char board[][SECTION_SIZE][SECTION_SIZE], int section, int row,
 * int col, int isXturn *
* The output: if possible, updates the board with the given coordinates and
 * return status code 0, otherwise, return error code 1 *
* The Function operation: check if the given coordinates are empty and if
 * they are, update the board, else, don't update the board and send error
 * code *
*************************************************************************/
int updateBoard(char board[][SECTION_SIZE][SECTION_SIZE], int section,
                int row, int col, int isXturn) {
    int isSpotEmpty = board[section][row][col] == EMPTY_SPOT;
    if (isSpotEmpty) {
        board[section][row][col] = isXturn ? 'X' : 'O';
    }

    return !isSpotEmpty;
}

/************************************************************************
* function name: game *
* The Input: *
* The output: play 3d tic tac toe and print the winner or a tie. return
 * status code 1 if there is an error, 0 for no errors*
* The Function operation: parse input from stdin and calculate the game state *
*************************************************************************/
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
    while (input == '\n' || input == ' ') {
        input = getchar();
    }

    int chosenSection = 0, chosenRow = 0, chosenColumn = 0;
    while (input != '\n' && winner == NO_WINNER) {
        if (!isValidInput(input)) {
            while (input != '\n') {
                input = getchar();
            }
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

                if (updateBoard(board, chosenSection, chosenRow,
                                chosenColumn, isXturn)) {
                    while (input != '\n') {
                        input = getchar();
                    }
                    return 1;
                }

                // Can't have a winner before 8 turns (reduce compute time)
                if (index + 1 >= 7 * 3) {
                    winner = determineWinnerBoard(board, SECTION_SIZE, 0);
                }
                isXturn = !isXturn;
                break;
            }
            default: {
                while (input != '\n') {
                    input = getchar();
                }
                return 1;
            }
        }

        int foundSpace = 0;
        do {

            /* increment the loop by pointing to the next character in the
             * sequence and make sure the next character is a space (only
             * correct input is a sequence of 3*n digits seperated by a space */
            input = getchar();
            if (input != ' ' && input != '\n' && !foundSpace) {
                return 1;
            }
            foundSpace = 1;
        } while (input == ' ');
        ++index;
    }

    // if the number of characters is not a multiple of 3 there is an error
    if (index % 3 != 0) {
        while (input != '\n') {
            input = getchar();
        }
        return 1;
    }
    if (winner == NO_WINNER) {
        winner = determineWinnerBoard(board, SECTION_SIZE, 1);
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

/************************************************************************
* function name: main *
* The Input: *
* The output: asks the user for input and print messages accordingly *
* The Function operation: read input from stdin and call functions accordingly *
*************************************************************************/
int main() {
    printf("Would you like to start? (y/n)\n");
    while (1) {
        char choice = '0';
        scanf("%c", &choice);
        while (choice == '\n') {
            choice = getchar();
        }
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
        }
    }
    // end of while loop
}
