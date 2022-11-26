/******************************************
*Student name: Gal Dali
*Student ID: 322558297
*Exercise name: ex1
******************************************/

#include <stdio.h>

/************************************************************************
* function name: power *
* The Input: int base, int exponent *
* The output: base to the power of exponent *
* The Function operation: calculates base to the power of exponent and return the answer *
*************************************************************************/
int power(int base, int exponent);

/************************************************************************
* function name: convertSexagesimalToDecimal *
* The Input: char *sexagesimalForm *
* The output: decimal value of sexagesimalForm as an int *
* The Function operation: reads the sexagesimal string and return its corresponding value in base 10 *
*************************************************************************/
int convertSexagesimalToDecimal(char *sexagesimalForm);

/************************************************************************
* function name: countDigits *
* The Input: int decimal, int base *
* The output: number of digits in target base *
* The Function operation: takes a decimal number and returns the length of the number in the target base *
*************************************************************************/
int countDigits(int decimal, int base);

/************************************************************************
 * * function name: printDecimalFromSexagesimal *
 * * The Input: int decimal *
 * * The output: the sexagesimal representation of decimal *
 * * The Function operation: print the sexagesimal representation of a decimal number to stdout *
 * *************************************************************************/
void printDecimalInSexagesimalForm(int decimal);

/************************************************************************
* function name: printDecimalInBinaryForm *
* The Input: int decimal *
* The output: the binary representation of decimal *
* The Function operation: print the binary representation of a decimal number to stdout *
*************************************************************************/
void printDecimalInBinaryForm(int decimal);

/************************************************************************
* function name: getStrLen *
* The Input: const char str[] *
* The output: length of str *
* The Function operation: calculates the length of char array 'str' and return the result *
*************************************************************************/
int getStrLen(const char str[]);

/************************************************************************
* function name: getIndexOfItem *
* The Input: const char arr[], char item *
* The output: index of arr with corresponding item *
* The Function operation: returns the index of the first occurring item in the given array *
*************************************************************************/
int getIndexOfItem(const char arr[], char item);

/************************************************************************
* function name: floorLog2 *
* The Input: int decimal *
* The output: floor(log2(decimal)) *
* The Function operation: calculates and returns the log2 of decimal rounded down (floor)  *
*************************************************************************/
int floorLog2(int decimal);

// global variable that is being used in multiple functions
const char base60[60] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                         'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                         'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                         'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                         ';', '-', '=', '+', '!', '@', '#', '$',
                         '%', '^', '&', '*', '(', ')', '/',
                         '"', '>', '<','?', '\\', '.', '~', '}', '{'};

int power(int base, int exponent) {
    int answer = 1;
    int iterator;
    for (iterator = 0; iterator < exponent; ++iterator) {
        answer = base * answer;
    }

    return answer;
}

int convertSexagesimalToDecimal(char *sexagesimalForm) {
    const int base = 60;
    int decimalForm = 0;

    int lpointerIndex = 0;
    int rpointerIndex = getStrLen(sexagesimalForm) - 1;
    while (rpointerIndex >= 0) {

        // Find the decimal value of given digit
        int digitInBase10 = getIndexOfItem(base60, sexagesimalForm[rpointerIndex]);

        /* Calculate 60 to the power of n where n is the exponent.
        The exponent magnitude is defined by its index starting count from the right
        Therefor, the lpointerIndex will represent the magnitude of the exponent
        (we start indexing from the right whilst the computer is indexing from the left) */
        int multiplier = power(base, lpointerIndex);
        decimalForm += (digitInBase10 * multiplier);
        --rpointerIndex;
        ++lpointerIndex;
    }

    return decimalForm;
}

int countDigits(int decimal, int base) {
    int radix = 1;
    while (decimal > power(base, radix)) {
        ++radix;
    }

    return radix;
}

void printDecimalInSexagesimalForm(int decimal) {
    const int sexagesimalBase = 60;
    char answer[countDigits(decimal, sexagesimalBase)];
    int remainder = 0;
    int i = 0;

    // Convert to base 60
    while (decimal != 0) {
        remainder = decimal % sexagesimalBase;
        answer[i] = base60[remainder];
        decimal = (int) (decimal / sexagesimalBase);
        ++i;
    }

    // Flip the order of answer
    char actualAnswer[i];
    int rpointerIndex = i;
    int lpointerIndex = 0;
    while (rpointerIndex > 0) {
        actualAnswer[rpointerIndex - 1] = answer[lpointerIndex];
        --rpointerIndex;
        ++lpointerIndex;
    }

    // print the sexagesimal number
    int digit;
    for (digit = 0; digit < i; ++digit) {
        printf("%c", actualAnswer[digit]);
    }

    printf("\n");
}

void printDecimalInBinaryForm(int decimal) {
    const int binaryBase = 2;

    // the maximum length of the binary number is given by floor(log2(decimal)) + 1
    char answer[floorLog2(decimal) + 1];
    int remainder = 0;
    int actualSize = 0;

    // Convert to base 2
    while (decimal != 0) {
        remainder = decimal % binaryBase;
        answer[actualSize] = remainder;
        decimal = (int) (decimal / binaryBase);
        ++actualSize;
    }

    // Flip the order of answer
    char actualAnswer[actualSize];
    int rpointerIndex = actualSize;
    int lpointerIndex = 0;
    while (rpointerIndex > 0) {
        actualAnswer[rpointerIndex - 1] = answer[lpointerIndex];
        --rpointerIndex;
        ++lpointerIndex;
    }

    // print the binary number
    int bit;
    for (bit = 0; bit < actualSize; ++bit) {
        printf("%d", actualAnswer[bit]);
    }

    printf("\n");
}

int getStrLen(const char str[]) {
    int len = 0;
    while (str[len] != '\0') { // String terminates with a nullbyte
        ++len;
    }

    return len;
}

int getIndexOfItem(const char arr[], char item) {
    int i = 0;
    while (i < getStrLen(arr)) {
        if (arr[i] == item) {
            return i;
        }

        ++i;
    }

    return -1; // Not found
}

int floorLog2(int decimal) {
    int answer = 0;
    while (decimal > 1) {
        ++answer;
        decimal = decimal >> 1;
    }

    return answer;
}

int main() {
    // Part A
    // 1.
     printf("%d\n", convertSexagesimalToDecimal("1948"));
     printf("%d\n", convertSexagesimalToDecimal("1+3="));
     printf("%d\n", convertSexagesimalToDecimal("{()}"));

     // 2.
     printDecimalInBinaryForm(convertSexagesimalToDecimal("2023"));
     printDecimalInBinaryForm(convertSexagesimalToDecimal("{+}"));
     printDecimalInBinaryForm(convertSexagesimalToDecimal("~?."));
     printDecimalInBinaryForm(convertSexagesimalToDecimal("540"));

     // 3.
     printDecimalInSexagesimalForm(convertSexagesimalToDecimal("2023") &
                                     convertSexagesimalToDecimal("540"));
     printDecimalInSexagesimalForm(convertSexagesimalToDecimal("{+}") |
                                     convertSexagesimalToDecimal("{-}"));
     printDecimalInSexagesimalForm(convertSexagesimalToDecimal("2023") ^
                                     convertSexagesimalToDecimal("540"));

     // 4.
     // Add two binary numbers
     const int size = 8;
     char first[] = "01110011";
     char second[] = "01001000";
     int start = 0, end = size - 1;
     char answer[size];
     int carry = 0;
     while (start < size) {

         // " - '0' " in order to convert '0' (char) to 0 (int)
         int fval = (int) (first[end - start] - '0');
         int sval = (int) (second[end - start] - '0');

         // xor will add two binary numbers
         answer[end - start] = (fval ^ sval) ^ carry;
         if ((fval == 0 && sval == 0 && carry == 0)\
          || (fval == 0 && sval == 0 && carry == 1)\
          || (fval == 0 && sval == 1 && carry == 0)\
          || (fval == 1 && sval == 0 && carry == 0)) {
             carry = 0;
         }
         else if ((fval == 0 && sval == 1 && carry == 1)\
               || (fval == 0 && sval == 0 && carry == 1)\
               || (fval == 0 && sval == 1 && carry == 0)\
               || (fval == 1 && sval == 0 && carry == 1)\
               || (fval == 1 && sval == 1 && carry == 0)) {
             carry = 1;
         }
         else {
             carry = 1;
         }

         ++start;
     } // end of while loop


     // get the MSB of the number to check for overflow
     if (answer[0] == 1) {
         printf("overflow");
     }
     else {
         int bitIndex;
         for (0; bitIndex < size; ++bitIndex) {
             printf("%d", answer[bitIndex]);
         }
     }

     printf("\n");

     // Part B
     printf("\"hello\\/\\/orld%%d\\n\",x;\n");

     return 0;
}
