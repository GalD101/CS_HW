#include "stdio.h"

//#define EMPTY_SPOT '*'
#define SECTION_SIZE 4

// TODO: if there is a winner, finish the game and clean buffer using while and getchar()


// TODO
int isValidInput(int x, int y, int z) { // , int board [][]
    return (x == 0 || x == 1 || x == 2 || x == 3) &&
           (y == 0 || y == 1 || y == 2 || y == 3) &&
           (z == 0 || z == 1 || z == 2 || z == 3);
}

void initSection(char section[][SECTION_SIZE], int size, char initVal) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            section[i][j] = initVal;
        }
    }
}

enum pos {
    section = 0,
    row = 1,
    column = 2,
};

void printRow(char row[], int size) {
    for (int i = 0; i < SECTION_SIZE; i++) {
        setbuf(stdout, 0);
        printf("%c ", row[i]);
    }
    setbuf(stdout, 0);
    printf("\n");
}

void printSection(int sectionIndex, char section[], int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            setbuf(stdout, 0);
            printf("(%d %d %d)", sectionIndex, i, j);
        }
        printf(" ");
        for (int k = i*size; k < size*(i+1); k++) {
            setbuf(stdout, 0);
            printf("%c ", section[k]);
        }
        printf("\n");
    }
}

int determineWinner(char ) {

}

// game() will return 0 if there is a winner or a tie. It will return a 1 if there was an error

int game() {
    const char EMPTY_SPOT = '*';
    int winner = 0;
    int isTie  = 0;
    char section0 [SECTION_SIZE][SECTION_SIZE];
    char section1 [SECTION_SIZE][SECTION_SIZE];
    char section2 [SECTION_SIZE][SECTION_SIZE];
    char section3 [SECTION_SIZE][SECTION_SIZE];

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
    while (!winner && !isTie) { //!(winner || isTie)
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
                            // todo:error
                            break;
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
                            // todo:error
                            break;
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
                    }

                    if (chosenSection != -1 && chosenRow != -1 && chosenColumn != -1) { //we have all the info we need!
                        switch (chosenSection) {
                            case 0: //todo: use a damn function
                                if (section0[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section0[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }
                                printf("input incorrect\n"); // todo:error
                                return 1;
                            case 1:
                                if (section1[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section1[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }
                                printf("input incorrect\n"); // todo:error
                                return 1;
                            case 2:
                                if (section2[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section2[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }
                                printf("input incorrect\n"); // todo:error
                                return 1;
                            case 3:
                                if (section3[chosenRow][chosenColumn] == EMPTY_SPOT) {
                                    section3[chosenRow][chosenColumn] = isXturn ? 'X':'O';
                                    break;
                                }
                                printf("input incorrect\n"); // todo:error
                                return 1;
                        }
                        isXturn = !isXturn;
                        break;
                    }
                }
                default: {
                    // todo:error
                    break;
                }
            }
            do {
                input = getchar();
            } while (input == ' ');
            ++index;
        }
        printSection(0, section0, SECTION_SIZE);
        printf("\n");
        printSection(1, section1, SECTION_SIZE);
        printf("\n");
        printSection(2, section2, SECTION_SIZE);
        printf("\n");
        printSection(3, section3, SECTION_SIZE);

        break;
        determineWinner(section0);
    }
}


int main () {
    printf("Would you like to start? (y/n)\n");
    while(1) {
        char choice;
        scanf("%c", &choice);
        switch (choice) {
            case 'y':
                printf("Please enter your game sequence.\n");
                if (!game()) {
                    printf("YEET\n");
                    return 0;
                }
                else {
                    printf("Would you like to continue? (y/n)\n");
                    break;
                }
                break;
            case 'n':
                printf("YEET\n");
                return 0;
            default:
//                printf("Would you like to continue? (y/n)\n");
                break;
        }
    }
    return 0;
}