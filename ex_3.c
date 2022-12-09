/******************************************
*Student name: Gal Dali
*Student ID: 322558297
*Exercise name: ex3
******************************************/

#include <stdio.h>

/************************************************************************
* function name: printMenu *
* The Input:  *
* The output: the menu with all the available options *
* The Function operation: prints a menu
 * with the options #'s and description *
*************************************************************************/
void printMenu() {
    printf("Choose an option:\n");
    printf("\t1: Logical Statement Calculator\n");
    printf("\t2: Count digit in a number\n");
    printf("\t3: GCD Calculator\n");
    printf("\t4: Exit\n");
}

/************************************************************************
* function name: countDigit *
* The Input: int number, int digit, int occurrences *
* The output: the number of occurrences of the digit in the number *
* The Function operation: calculates the number
 * of occurrences of digit in number *
*************************************************************************/
int countDigit(int number, int digit, int occurrences) {
    if (number == 0) {
        return occurrences;
    }
    if ((number % 10) == digit) {
        ++occurrences;
    }
    return countDigit(number / 10, digit, occurrences);
}

/************************************************************************
* function name: gcd *
* The Input: int a, int b *
* The output: the greatest common divider of numbers a and b *
* The Function operation: calculates the greatest common divider of the
 * numbers a and b *
*************************************************************************/
long long int gcd(long long int a, long long int b) {
    int min = 0, max = 0;
    if (a == 0) {
        printf("GCD = %lld\n", b);
        return b;
    }
    if (b == 0) {
        printf("GCD = %lld\n", a);
        return a;
    }
    if (a > b) {
        max = a;
        min = b;
    } else {
        max = b;
        min = a;
    }
    int num = 0;
    int copyMax = max;
    while (copyMax - min >= 0) {
        copyMax -= min;
        ++num;
    }
    printf("%lld*%lld+%lld = %lld (num1=%d, num2=%d)\n", min, num,
           (max - min * num), max, max, min);
    gcd(min, max - min * num);
}

/************************************************************************
* function name: printSyntaxError *
* The Input:  *
* The output: "You have a syntax error in your statement" *
* The Function operation: prints the error message to the screen *
*************************************************************************/
void printSyntaxError() {
    printf("You have a syntax error in your statement.\n");
}

/************************************************************************
* function name: isDigit *
* The Input: char c *
* The output: 1 if c is a digit, 0 otherwise *
* The Function operation: calculates whether or not c is a digit *
*************************************************************************/
int isDigit(char c) {
    return (c >= '0' && c <= '9');
}

/************************************************************************
* function name: isAlpha *
* The Input: char c *
* The output: 1 if c is an alphabetic letter, 0 otherwise *
* The Function operation: calculates whether or not
 * c is an alphabetic letter *
*************************************************************************/
int isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/************************************************************************
* function name: isValidVar *
* The Input: char c *
* The output: 1 if c is a digit or an alphabetic letter, 0 otherwise *
* The Function operation: calculates whether or
 * not c is a digit or an alphabetic letter *
*************************************************************************/
int isValidVar(char c) {
    return isAlpha(c) || isDigit(c);
}

/************************************************************************
* function name: isValidRelationOperator *
* The Input: char c *
* The output: 1 if c is a & or |, 0 otherwise *
* The Function operation: calculates whether or not c is a & or | *
*************************************************************************/
int isValidRelationOperator(char c) {
    return (c == '&') || (c == '|') || (c == '^');
}

/************************************************************************
* function name: isValidMathOperator *
* The Input: char c *
* The output: 1 if c is a = or > or < |, 0 otherwise *
* The Function operation: calculates whether or not c is a = or > or < *
*************************************************************************/
int isValidMathOperator(char c) {
    return (c == '=') || (c == '>') || (c == '<');
}

/************************************************************************
* function name: isCaps *
* The Input: char letter *
* The output: 1 if c is a capital letter, 0 otherwise *
* The Function operation: calculates whether or not c is a capital letter *
*************************************************************************/
int isCaps(char letter) {
    return letter >= 'A' && letter <= 'Z';
}

/************************************************************************
* function name: parseStatement *
* The Input: char var1, char var2, char op, char isNot *
* The output: 1 if the statement (var1 op var2) is true, 0 otherwise *
* The Function operation: calculates whether or not
 * the statement is true or false *
*************************************************************************/
int parseStatement(int var1, int var2, char op, int isNot, int isVar1Char,
                   int isVar2Char) {
    switch (op) {
        case '=':
            if (var1 == var2) {
                return !isNot;
            } else if (var1 < var2) {
                if (isVar1Char) {
                    return (var1 + ('a' - 'A') == var2) ? !isNot : isNot;
                } else if (isVar2Char) {
                    return (var2 + ('a' - 'A') == var1) ? !isNot : isNot;
                }
                return isNot;
            } else if (var1 > var2) {
                if (isVar2Char) {
                    return (var2 + ('a' - 'A') == var1) ? !isNot : isNot;
                } else if (isVar1Char) {
                    return (var1 + ('a' - 'A') == var2) ? !isNot : isNot;
                }
                return isNot;
            }
            break;
        case '>':
            if (isVar1Char && isVar2Char) {
                if (isCaps(var1)) {
                    if (isCaps(var2)) {

                        // both var1 and var2 are caps
                        return (var1 > var2) ? !isNot : isNot;
                    } else {

                        // var1 is caps and var2 is small
                        return (var1 + ('a' - 'A') > var2) ? !isNot : isNot;
                    }
                } else {
                    if (isCaps(var2)) {

                        // var1 is small and var2 is caps
                        return (var1 > var2 + ('a' - 'A')) ? !isNot : isNot;
                    } else {

                        // var1 is small and var2 is small
                        return (var1 > var2) ? !isNot : isNot;
                    }
                }
            }
            return (var1 > var2) ? !isNot : isNot;
        case '<':
            if (isVar1Char && isVar2Char) {
                if (isCaps(var1)) {
                    if (isCaps(var2)) {
                        return (var1 < var2) ? !isNot : isNot;
                    } else {

                        // var1 is caps and var2 is small
                        return (var1 + ('a' - 'A') < var2) ? !isNot : isNot;
                    }
                } else {
                    if (isCaps(var2)) {

                        // var1 is small and var2 is caps
                        return (var1 < var2 + ('a' - 'A')) ? !isNot : isNot;
                    } else {

                        // var1 is small and var2 is small
                        return (var1 < var2) ? !isNot : isNot;
                    }
                }
            }
            return (var1 < var2) ? !isNot : isNot;
        default:
            return 0;
    }
}

/************************************************************************
* function name: printPositiveMessage *
* The Input:  *
* The output: "You should stay positive, and so should your input. *
* The Function operation: prints the positive message to the screen *
*************************************************************************/
void printPositiveMessage() {
    printf("You should stay positive, and so should your input.\n");
}


/************************************************************************
* function name: printNumOfOccurrences *
* The Input: int digit, int occurrences, int number *
* The output: "The digit digit appears
 * occurrences times in the number number" *
* The Function operation: prints the digit, the number
 * and the number of occurrences to the screen *
*************************************************************************/
int printNumOfOccurrences(int digit, int occurrences, long long int number) {
    printf("The digit %d appears %d times in the number %lld\n",
           digit, occurrences, number);
}


/************************************************************************
* function name: printDefaultMessage *
* The Input:  *
* The output: "Fool of a Took!\nThis is a serious journey, not a hobbit walking-party.\n
 * Throw yourself in next time, and then you will be no further nuisance.\n" *
* The Function operation: prints the default message to the screen *
*************************************************************************/
void printDefaultMessage() {
    printf("Fool of a Took!\n"
           "This is a serious journey, not a hobbit walking-party.\n"
           "Throw yourself in next time, "
           "and then you will be no further nuisance.\n");
}

/************************************************************************
* function name: handleChoice *
* The Input: int choice *
* The output: executes the corresponding operation
 * with respect to the given choice *
* The Function operation: operating according to the choice *
*************************************************************************/
int handleChoice(int choice) {
    switch (choice) {
        case 1: {
            printf("\nPlease write your logical statement: ");
            char ch = 0;
            scanf(" %c", &ch);

            int var1 = -1, var2 = -1;
            int isVar1Digit = 0, isVar2Digit = 0;
            char operation = 0;
            int isNot = 0;
            int numOfOpeningBraces = 0, numOfClosingBraces = 0;
            char relationOperator;
            int statementVal = 0;
            int isError = 0;
            while (ch != '\n' && ch != ' ' && ch != EOF) {
                if (var1 != -1 && operation != 0 && var2 != -1 &&
                    numOfOpeningBraces == numOfClosingBraces) {
                    if (isValidRelationOperator(relationOperator)) {
                        switch (relationOperator) {
                            case '&':
                                statementVal = statementVal &&
                                               (parseStatement(var1, var2,
                                                               operation, isNot,
                                                               !isVar1Digit,
                                                               !isVar2Digit));
                                break;
                            case '|':
                                statementVal = statementVal ||
                                               (parseStatement(var1, var2,
                                                               operation, isNot,
                                                               !isVar1Digit,
                                                               !isVar2Digit));
                                break;
                            default:
                                break;
                        }
                    } else {
                        statementVal = parseStatement
                                (var1, var2, operation, isNot,
                                 !isVar1Digit, !isVar2Digit);
                    }

                    // Reset vars for new potential statement
                    var1 = -1;
                    var2 = -1;
                    isVar1Digit = 0;
                    isVar2Digit = 0;
                    operation = 0;
                    ch = getchar();
                    isNot = 0;
                    continue;
                } else {
                    int validVar = isValidVar(ch);
                    int openBraces = (ch == '(');
                    int closeBraces =
                            (ch == ')') && (var2 != -1) && (operation != 0);
                    int notSign = (ch == '~');
                    int validMathOp = isValidMathOperator(ch);
                    int validRelationOp = isValidRelationOperator(ch);

                    if (validVar || openBraces || notSign ||
                        validMathOp || closeBraces || validRelationOp) {
                        if (validVar) {

                            // Set vars
                            if (var1 == -1) {
                                isVar1Digit = isDigit(ch);
                                var1 = isVar1Digit ? ch - '0' : ch;
                                ch = getchar();

                                // In the case of a letter followed by another letter, print error
                                if (isAlpha(ch) && isAlpha(var1)) {
                                    if (!isError) {
                                        printSyntaxError();
                                    }
                                    isError = 1;
                                    break;
                                }

                                // in the case of a number bigger or equals to 10
                                int num = (int) var1;
                                while (isDigit(ch) && isVar1Digit) {
                                    num *= 10;
                                    ch -= '0';
                                    num += ch;
                                    ch = getchar();
                                }
                                var1 = num;
                                continue;
                            } else if (var2 == -1) {
                                isVar2Digit = isDigit(ch);
                                var2 = isVar2Digit ? ch - '0' : ch;
                                ch = getchar();

                                // In the case of a letter followed by another letter, print error
                                if (isAlpha(ch) && isAlpha(var2)) {
                                    if (!isError) {
                                        printSyntaxError();
                                    }
                                    isError = 1;
                                    break;
                                }

                                // in the case of a number bigger or equals to 10
                                int num = (int) var2;
                                while (isDigit(ch) && isVar2Digit) {
                                    num *= 10;
                                    ch -= '0';
                                    num += ch;
                                    ch = getchar();
                                }
                                var2 = num;
                                continue;
                            }
                        } else if (openBraces) {
                            ++numOfOpeningBraces;
                            ch = getchar();
                            continue;
                        } else if (notSign) {
                            isNot = !isNot;
                            ch = getchar();
                            continue;
                        } else if (validMathOp) {
                            operation = ch;
                            ch = getchar();
                            continue;
                        } else if (closeBraces) {
                            ++numOfClosingBraces;
                            continue;
                        } else if (validRelationOp) {
                            relationOperator = ch;
                            var1 = -1;
                            var2 = -1;
                            isVar1Digit = 0;
                            isVar2Digit = 0;
                            ch = getchar();
                            continue;
                        }
                    } else {
                        if (!isError) {
                            printSyntaxError();
                        }
                        isError = 1;
                        break;
                    }
                }
            } // end of while loop
            if (numOfOpeningBraces != numOfClosingBraces) {
                if (!isError) {
                    printSyntaxError();
                }

                isError = 1;
                while (ch != '\n' && ch != ' ') {
                    ch = getchar();
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
        case 2: {
            printf("\nEnter a number and a digit: ");
            long long int number = 0;
            int digit = 0;
            scanf("%lld %d", &number, &digit);
            if (digit >= 10 || digit < 0 || number < 0) {
                printPositiveMessage();
                break;
            } else if (number == 0) {
                printNumOfOccurrences(digit, digit == 0 ? 1 : 0, number);
                break;
            }
            int copyNumber = number, copyDigit = digit;
            int occurrences = countDigit(copyNumber, copyDigit, 0);
            printNumOfOccurrences(digit, occurrences, number);
            break;
        }
        case 3: {
            printf("\nEnter two positive numbers: ");
            long long int num1, num2;
            scanf("%lld %lld", &num1, &num2);
            if (num1 < 0 || num2 < 0) {
                printPositiveMessage();
                break;
            }
            gcd(num1, num2);
            break;
        }
        case 4:
            printf("So Long, and Thanks for All the Fish!\n");
            return 0;
        default:
            printDefaultMessage();
            break;
    }
    return 1;
}

/************************************************************************
* function name: main *
* The Input:  *
* The output: prints the menu until user aborts
 * and check the validity of the input *
* The Function operation: calling functions and
 * checking the validity of the input *
*************************************************************************/
int main() {
    while (1) {
        printMenu();
        int choice = 0;
        int isValidInput = scanf(" %d", &choice);
        if (isValidInput != 1) {
            printDefaultMessage();
            scanf("%*[^ ]");
            continue;
        }
        if (!handleChoice(choice)) {
            break;
        }
    }

    return 0;
}
