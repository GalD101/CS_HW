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
    printf("%d*%d+%d = %d (num1=%d, num2=%d)\n", min, num, copyMax - min*num, min*num + (copyMax - min*num), min*num + (copyMax - min*num), min);
    gcd(min, copyMax - min*num);

}

//int gcd2(int num1, int num2) {
//    if (num1 == 0) {
//        return num2;
//    }
//    return gcd2(num2%num1, num1);
//}

void printSyntaxError() {
    printf("You have a syntax error in your statement.\n");
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

int parseStatement(char var1, char var2, char op, int isNot) {
    switch (op) {
        case '=':
            if (var1 == var2) {
                return !isNot;
            } else if (var1 < var2) {
                return (var1 + ('a' - 'A') == var2) ? !isNot : isNot;
            } else if (var1 > var2) {
                return (var1 == var2 + ('a' - 'A')) ? !isNot : isNot;
            } else {
                return !isNot;
            }
            //break; // useless break because of return
        case '>':
            return (var1 > var2) ? !isNot : isNot;
        case '<':
            return (var1 < var2) ? !isNot : isNot;
        default:
            return 0;
            //break;
    }
}

int handleChoice(int choice) {
    switch (choice) {
        case 1: {
            printf("\nPlease write your logical statement: ");
            char ch = 0;
            scanf(" %c", &ch);
            int isTrue = 0;
            char operation = 0;
            char var1 = -1, var2 = -1; // -1 means they are unset
            int isNot = 0;
            int index = 0;
            int numOfOpeningBraces = 0;
            int numOfClosingBraces = 0;
            int isStatementDone = 0;
            int numOfStatementsParsed = 0;
            char relationOperator;
            int statementVal = 0;
            int isError = 0;
            while (ch != '\n' && ch != ' ') {
                if (var1 != -1 && operation != 0 && var2 != -1 && numOfOpeningBraces == numOfClosingBraces) { // var1 is set and operation is set and var2 is set (the latter check is the most important one. after var2 there will be at least 1 ')')
                    if (isValidRelationOperator(relationOperator)) {
                        switch (relationOperator) {
                            case '&':
                                statementVal = statementVal&&(parseStatement(var1, var2, operation, isNot));
                                break;
                            case '|':
                                statementVal = statementVal||(parseStatement(var1, var2, operation, isNot));
                                break;
                            default:
                                break;
                        }
                    }
                    else {
                        statementVal = parseStatement(var1, var2, operation, isNot); // 1 = true, 0 = false
                    }
                    ++numOfStatementsParsed;
                    var1 = -1;
                    var2 = -1;
                    operation = 0;
                    ch = getchar();
                    index = 0;
                    isNot = 0;
                    // finito
                    continue;
                }
                else { // if (numOfOpeningBraces > 0)
                    int validVar = isValidVar(ch); // isAlpha(ch) || isDigit(ch)
                    int openBraces = (ch == '(');
                    int closeBraces = (ch == ')') && (var2 != -1) && (operation != 0);
                    int notSign = (ch == '~');
                    int validMathOp = isValidMathOperator(ch);
                    int validRelationOp = isValidRelationOperator(ch);

                    if (!validVar && !openBraces && !notSign && !validMathOp && !closeBraces && !validRelationOp) { //todo flip the if and switch with else block todo: go fuck yourself
                        if (!isError) {
                            printSyntaxError();
                        }
                        isError = 1;
                        while(ch != ' ') { //clean buffer
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
                                var1 = isDigit(ch) ? ch - '0': ch;
                                ch = getchar();
                                ++index;
                                continue;
                            }
                            else if (var2 == -1) {
                                var2 = isDigit(ch) ? ch - '0': ch;
                                ch = getchar();
                                ++index;
                                continue;
                                // next should be ')'.
                            }
                        }
                        else if (openBraces) { // ch is '('
                            ++numOfOpeningBraces;
                            ch = getchar();
                            ++index;
                            continue;
                        }
                        else if (notSign) { // ch is '~'
                            isNot = !isNot;
                            ch = getchar();
                            ++index;
                            continue;
                        }
                        else if (validMathOp) {
                            operation = ch;
                            ch = getchar();
                            ++index;
                            continue;
                        }
                        else if (closeBraces) {
                            ++numOfClosingBraces;
                            continue;
                        }
                        else if (validRelationOp) {
                            relationOperator = ch;
                            var1 = -1;
                            var2 = -1;
                            index = 0;
                            ch = getchar();
                            continue;
                        }
                    }
                }
            }
            if (numOfOpeningBraces != numOfClosingBraces) {
                if (!isError) {
                    printSyntaxError();
                }
                isError = 1;
                while(ch != ' ') { //clean buffer
                    ch = getchar();
                    ++index;
                }
                break;
            }
            if (statementVal) {
                printf("The statement is true.\n");
            } else {
                printf("The statement is false.\n");
            }
            break;
        }
        case 2:
        {
            printf("Enter a number and a digit: ");
            int number = 0, digit = 0;
            scanf("%d %d", &number, &digit);
            if (digit >= 10 || digit < 0 || number < 0) {
                printf("You should stay positive, and so should your input.\n");
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
            printf("\nEnter two positive numbers: ");
            int num1, num2;
            scanf("%d %d", &num1, &num2);
            if (num1 < 0 || num2 < 0) {
                printf("You should stay positive, and so should your input.\n");
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
    return 1;
}
int main () {
    while (1) {
        printMenu();
        int choice = 0;
        int isValidInput = scanf(" %d", &choice);
        if (isValidInput != 1) {
            setbuf(stdout, 0);
            printf("Fool of a Took!\n"
                   "This is a serious journey, not a hobbit walking-party.\n"
                   "Throw yourself in next time, and then you will be no further nuisance.\n");
            scanf("%*[^ ]");
            continue;
        }
        if (!handleChoice(choice)) {
            break;
        }

    }
    return 0;
}