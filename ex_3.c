#include <stdio.h>
#include <math.h>

void printMenu() {
    printf("Choose an option:\n");
    printf("\t1: Logical Statement Calculator\n");
    printf("\t2: Count digit in a number\n");
    printf("\t3: GCD Calculator\n");
    printf("\t4: Exit\n");
}

//int countDigit(int number, int digit) {
//    static int occurrences = 0;
//    while (number != 0) {
//        int remainder = number % 10;
//        if (remainder == digit) {
//            ++occurrences;
//        }
//        number /= 10;
//    }
//    return occurrences;
//}

int countDigit(int number, int digit, int occurrences) {
    if (number == 0) {
        return occurrences;
    }
    if ((number % 10) == digit) {
        ++occurrences;
    }
    return countDigit(number / 10, digit, occurrences);
}

int handleChoice(int choice) {
    switch (choice) {
        case 1:
            printf("Please write your logical statement: ");
            char ch = 0;
            fseek(stdin, 0, SEEK_END);
            int isTrue = 0;
            char operation = 0;
            char fArg = -1, sArg = -1;
            int isNot = 0;
            int index = 0;
            while (ch != '\n') {
                ch = getchar();
                switch (ch) {
                    case '(':
                    case ')':
                        continue;
                    case '~':
                        isNot = !isNot;
                        break;
                    default:
                        break;
                }
                if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                    if (fArg == -1) {
                        fArg = ch;
                        continue;
                    }
                    if (sArg == -1) {
                        sArg = ch;
                    }
                }
                else if (ch == '>' || ch == '<' || ch == '=') {
                    operation = ch;
                }
                ++index;
            }
            switch (operation) {
                case '>':
                    isTrue = (fArg > sArg) ? !isNot: isNot;
                    break;
                case '<':
                    isTrue = (fArg < sArg) ? !isNot: isNot;
                    break;
                case '=':
                    if (fArg == sArg) {
                        isTrue = !isNot;
                    }
                    else if (fArg < sArg) {
                        isTrue = (fArg + ('a' - 'A') == sArg) ? !isNot: isNot;
                    }
                    else if (fArg > sArg) {
                        isTrue = (fArg == sArg + ('a' - 'A')) ? !isNot: isNot;
                    }
                    else {
                        isTrue = !isNot;
                    }
                    break;
                default:
                    isTrue = 0;
                    break;
            }
            if (isTrue) {
                printf("The statement is true.\n");
            }
            else {
                printf("The statement is false.\n");
            }
//            while ((ch = getchar()) != '\n' && ch != EOF) {
//                printf("%c", ch);\

//            }
//            fflush(stdin);
//            inputChar = ge5tchar();
//            int i = 0;
//            while ( != '\n') {
//                fflush(stdin);
//                scanf("%c", &a);
//                printf("%c", a);
//                ++i;
//            }
            break;
        case 2:
            printf("Enter a number and a digit: ");
            int number = 0, digit = 0;
            scanf("%d %d", &number, &digit);
            if (digit >= 10 || digit < 0) {
                printf("Invalid input!\n");
                break;
            }
            printf("The digit %d appears %d times in the number %d\n", (digit, number, countDigit(number, digit, 0)));
            break;
        case 3:
            break;
        case 4:
            printf("So Long, and Thanks for All the Fish!\n");
            return 0;
        default:
            printf("Fool of a Took!\n"
                   "This is a serious journey, not a hobbit walking-party.\n"
                   "Throw yourself in next time, and then you will be no further nuisance.\n");
            break;
    }
    return choice;
}
int main () {
    while (1) {
        printMenu();
        int choice;
        scanf("%d", &choice);
        if (!handleChoice(choice)) {
            break;
        }

    }
    return 0;
}