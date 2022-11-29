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


int gcd(int a, int b) {
    int min = 0, max = 0;
    if (a == 0) {
        printf("GCD = %d\n", b);
        return b;
    }
    if (b == 0) {
        printf("GCD = %d\n", a);
        return a;
    }
    if (a > b) {
        max = a;
        min = b;
    }
    else {
        max = b;
        min = a;
    }
    int num = 0;
    int copyMax = max, copyMin = min;
    while (max - min >= 0) {
        max -= min;
        ++num;

    }
    printf("%d*%d + %d = %d (num1=%d, num2=%d)\n", min, num, copyMax - min*num, min*num + (copyMax - min*num), min*num + (copyMax - min*num), min);
    gcd(min, copyMax - min*num);

}

//int gcd2(int num1, int num2) {
//    if (num1 == 0) {
//        return num2;
//    }
//    return gcd2(num2%num1, num1);
//}

void printSyntaxError() {
    printf("You have a syntax error in your statement\n");
}

int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

int isAlpha(char c) {
    return (c >='a' && c <='z') || (c >='A' && c<= 'Z');
}

int isValidVar(char c) {
    return isAlpha(c) || isDigit(c);
}

int isValidRelationOperator(char c) {
    return (c == '&') || (c == '|') || (c == '^');
}

int isValidMathOperator(char c) {
    return (c == '=') || (c == '>') || (c == '<');
}

int handleChoice(int choice) {
    switch (choice) {
        case 1: {
            printf("Please write your logical statement: ");
            char ch = 0;
            scanf(" %c ", &ch);
            int isTrue = 0;
            char operation = 0;
            char var1 = -1, var2 = -1; // -1 means they are unset
            int isNot = 0;
            int index = 0;
            int numOfOpeningBraces = 0;
            int isStatementDone = 0;
            char relationOperator;
            while (ch != '\n' && ch != ' ') {
                if (numOfOpeningBraces == 0) { // same as if (numOfOpeningBraces == 0)
                    if (ch = '(') {
                        ++numOfOpeningBraces; // numOfOpeningBraces = !numOfOpeningBraces;
                        // next should be var1 or ( or ~
                    }
                    else if (ch = '~') {
                        isNot = !isNot;
                        // next can be '~' or '('
                    }
                }
                else { // if (numOfOpeningBraces > 0)
                    int validVar = isValidVar(ch); // isAlpha(ch) || isDigit(ch)
                    int openBraces = (ch == '(');
                    int notSign = (ch == '~');

                    if (!validVar && !openBraces && !notSign) { //todo flip the if and switch with else block
                        printSyntaxError();
                        while(ch != '\n') { //clean buffer
                            ch = getchar();
                            ++index;
                        }
                        break;
                        // invalid!!!!
                    }
                    else { // ch is VALID!!!
                        if (validVar) { // ch is variable
                            // set vars
                            if (var1 == -1) {
                                var1 = isDigit ? ch - '0': ch;
                                ch = getchar();
                                ++index;
                                break;
                            }
                            else if (var2 == -1) {
                                var2 = isDigit ? ch - '0': ch;
                                ch = getchar();
                                ++index;
                                break;
                            }
                        }
                        else if (openBraces) { // ch is '('
                            ++numOfOpeningBraces;
                            ch = getchar();
                            ++index;
                            break;
                        }
                        else if (notSign) { // ch is '~'
                            isNot = !isNot;
                            ch = getchar();
                            ++index;
                            break;
                        }
                    }
                }
                if (var1 != -1) { // var1 is set!
                    // should be a math op
                    if (isValidMathOperator(ch)) {
                        operation = ch;
                        ch = getchar();
                        ++index;
                        break;
                        // next should be var2!
                    }
                    else {
                        printSyntaxError();
                        //todo:clean buffer
                        break;
                    }
                }
                if (operation != 0 && var1 != -1) {
                    if (isValidVar(ch)) {
                        var2 = isDigit ? ch - '0': ch;
                        ch = getchar();
                        ++index;
                        break;
                    }
                }
                if (var1 != -1 && operation != 0 && var2 != -1){ // var1 is set and operation is set and var2 is set

                }

                if (isStatementDone && ((ch == '&') || (ch == '|') || (ch == '^'))) { // next should be '~' or '('
                    isStatementDone = 0;
                    relationOperator = ch;
                    switch (operation) {
                        case '>':
                            isTrue = (var1 > var2) ? !isNot : isNot;
                            break;
                        case '<':
                            isTrue = (var1 < var2) ? !isNot : isNot;
                            break;
                        case '=':
                            if (var1 == var2) {
                                isTrue = !isNot;
                            } else if (var1 < var2) {
                                isTrue = (var1 + ('a' - 'A') == var2) ? !isNot : isNot;
                            } else if (var1 > var2) {
                                isTrue = (var1 == var2 + ('a' - 'A')) ? !isNot : isNot;
                            } else {
                                isTrue = !isNot;
                            }
                            break;
                        default:
                            isTrue = 0;
                            break;
                    }
                }
                if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
                    if (var1 == -1) {
                        var1 = ch;
                    }
                    else if (var2 == -1) {
                        var2 = ch;
                    }
                } else if ((ch >= '0' && ch <= '9')) {
                    ch = ch - '0';
                } else if (ch == '>' || ch == '<' || ch == '=') {
                    operation = ch;
                }
                ++index;
                ch = getchar();
            }
            switch (operation) {
                case '>':
                    isTrue = (var1 > var2) ? !isNot : isNot;
                    break;
                case '<':
                    isTrue = (var1 < var2) ? !isNot : isNot;
                    break;
                case '=':
                    if (var1 == var2) {
                        isTrue = !isNot;
                    } else if (var1 < var2) {
                        isTrue = (var1 + ('a' - 'A') == var2) ? !isNot : isNot;
                    } else if (var1 > var2) {
                        isTrue = (var1 == var2 + ('a' - 'A')) ? !isNot : isNot;
                    } else {
                        isTrue = !isNot;
                    }
                    break;
                default:
                    isTrue = 0;
                    break;
            }
            if (isTrue) {
                printf("The statement is true.\n");
            } else {
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
        }
        case 2:
        {
            printf("Enter a number and a digit: ");
            int number = 0, digit = 0;
            scanf("%d %d", &number, &digit);
            if (digit >= 10 || digit < 0) {
                printf("Invalid input!\n");
                break;
            } else if (number == 0 && digit == 0) {
                printf("The digit %d appears %d times in the number %d\n", digit, 1, number);
                break;
            } else if (number == 0) {
                printf("The digit %d appears %d times in the number %d\n", digit, 0, number);
                break;
            }
            int copyNumber = number, copyDigit = digit;
            int occurrences = countDigit(copyNumber, copyDigit, 0);
            printf("The digit %d appears %d times in the number %d\n", digit, occurrences, number);
            break;
        }
        case 3:
        {
            printf("Enter two positive numbers: ");
            int num1, num2;
            scanf("%d %d", &num1, &num2);
            if (num1 < 0 || num2 < 0) {
                printf("Invalid input!\n");
                break;
            }
            if (num1 > num2) {
                gcd(num1, num2);
//                int m = gcd2(num1, num2);
//                printf("%d\n", m);
            }
            else {
                gcd(num2, num1);
//                int n = gcd2(num2, num1);
//                printf("%d\n", n);
            }
            break;
        }
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
        scanf(" %d", &choice);
        if (!handleChoice(choice)) {
            break;
        }

    }
    return 0;
}