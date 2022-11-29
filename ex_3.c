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
* The Function operation: prints a menu with the options #'s and description *
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
* The output: count the # of occurrences of the given digit in the aforementioned input number *
* The Function operation: calculates the number of occurrences of the digit in the number *
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
* The Function operation: calculates the greatest common divider of the numbers a and b *
*************************************************************************/
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
* The Function operation: calculates whether or not c is an alphabetic letter *
*************************************************************************/
int isAlpha(char c) {
    return (c >='a' && c <='z') || (c >='A' && c<= 'Z');
}

/************************************************************************
* function name: isValidVar *
* The Input: char c *
* The output: 1 if c is a digit or an alphabetic letter, 0 otherwise *
* The Function operation: calculates whether or not c is a digit or an alphabetic letter *
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
    return (c == '&') || (c == '|');
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
* function name: parseStatement *
* The Input: char var1, char var2, char op, char isNot *
* The output: 1 if the statement (var1 op var2) is true, 0 otherwise *
* The Function operation: calculates whether or not the statement is true or false *
*************************************************************************/
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
        case '>':
            return (var1 > var2) ? !isNot : isNot;
        case '<':
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
* The output: "The digit digit appears occurrences times in the number number" *
* The Function operation: prints the digit, the number and the number of occurrences to the screen *
*************************************************************************/
void printNumOfOccurrences(int digit, int occurrences, int number) {
    printf("The digit %d appears %d times in the number %d\n", digit, occurrences, number);
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
           "Throw yourself in next time, and then you will be no further nuisance.\n");
}

/************************************************************************
* function name: handleChoice *
* The Input: int choice *
* The output: executes the corresponding operation with respect to the given choice *
* The Function operation: operating according to the choice *
*************************************************************************/
int handleChoice(int choice) {
    switch (choice) {
        case 1: {
            printf("\nPlease write your logical statement: ");
            char ch = 0;
            scanf(" %c", &ch);
            char operation = 0;
            char var1 = -1, var2 = -1; // -1 means they are unset
            int isNot = 0;
            int index = 0;
            int numOfOpeningBraces = 0;
            int numOfClosingBraces = 0;
            int numOfStatementsParsed = 0;
            char relationOperator;
            int statementVal = 0;
            int isError = 0;
            while (ch != '\n' && ch != ' ') {

                // var1 is set and operation is set and var2 is set and num and # of ( == # of )
                if (var1 != -1 && operation != 0 && var2 != -1 && numOfOpeningBraces == numOfClosingBraces) {
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

                    // reset variables
                    var1 = -1;
                    var2 = -1;
                    operation = 0;
                    ch = getchar();
                    index = 0;
                    isNot = 0;
                    continue;
                }
                else {
                    int validVar = isValidVar(ch); // isAlpha(ch) || isDigit(ch)
                    int openBraces = (ch == '(');
                    int closeBraces = (ch == ')') && (var2 != -1) && (operation != 0);
                    int notSign = (ch == '~');
                    int validMathOp = isValidMathOperator(ch);
                    int validRelationOp = isValidRelationOperator(ch);

                    if (validVar || openBraces || notSign || validMathOp || closeBraces || validRelationOp) {
                        if (validVar) {

                            // Set vars
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
                            }
                        }
                        else if (openBraces) {
                            ++numOfOpeningBraces;
                            ch = getchar();
                            ++index;
                            continue;
                        }
                        else if (notSign) {
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
                    else {
                        if (!isError) {
                            printSyntaxError();
                        }
                        isError = 1;
                        while(ch != ' ') {
                            ch = getchar();
                            ++index;
                        }
                        break;
                    }
                }
            }
            if (numOfOpeningBraces != numOfClosingBraces) {
                if (!isError) {
                    printSyntaxError();
                }
                isError = 1;
                while(ch != ' ') {
                    ch = getchar();
                    ++index;
                }
                break;
            }
            printf("The statement is %s\n", statementVal ? "true" : "false");
            break;
        }
        case 2:
        {
            printf("\nEnter a number and a digit: ");
            int number = 0, digit = 0;
            scanf("%d %d", &number, &digit);
            if (digit >= 10 || digit < 0 || number < 0) {
                printPositiveMessage();
                break;
            } else if (number == 0 && digit == 0) {
                printNumOfOccurrences(digit, 1, number);
                break;
            } else if (number == 0) {
                printNumOfOccurrences(digit, 0, number);
                break;
            }
            int copyNumber = number, copyDigit = digit;
            int occurrences = countDigit(copyNumber, copyDigit, 0);
            printNumOfOccurrences(digit, occurrences, number);
            break;
        }
        case 3:
        {
            printf("\nEnter two positive numbers: ");
            int num1, num2;
            scanf("%d %d", &num1, &num2);
            if (num1 < 0 || num2 < 0) {
                printPositiveMessage();
                break;
            }
            (num1 > num2) ? gcd(num1, num2) : gcd(num2, num1);
            break;
        }
        case 4:
            printf("So Long, and Thanks for All the Fish!");
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
* The output: prints the menu until user aborts and check the validity of the input *
* The Function operation: calling functions and checking the validity of the input *
*************************************************************************/
int main () {
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