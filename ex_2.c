/******************************************
*Student name: Gal Dali
*Student ID: 322558297
*Exercise name: ex2
******************************************/

#include <stdio.h>
#include <math.h>

/************************************************************************
* function name: main *
* The Input:  *
* The output: a menu with the associated options  *
* The Function operation: calculates the correct output given a valid input and option number *
*************************************************************************/
int main() {
    while (1) {
        printf("Choose an option:\n");
        printf("1. octal to hex\n");
        printf("2. binary addition\n");
        printf("3. print HI\n");
        printf("4. count bits\n");
        printf("5. decimal to binary\n");
        printf("6. Zig-Zag bits\n");
        printf("7. exit\n");

        int option = 0;
        scanf("%d", &option);

        switch (option) {
            case 1:
            {
                int isValidOctal = 1;
                printf("Please enter number in octal base: ");
                int octalBaseNumber = 0;
                scanf("%d", &octalBaseNumber);
                if (octalBaseNumber < 7 && octalBaseNumber >= 0) {
                    printf("%d\n", octalBaseNumber);
                    break;
                }
                if (octalBaseNumber < 0) {
                    setbuf(stdout, 0);
                    printf("Invalid input!\n");
                    isValidOctal = 0;
                    break;
                }
                int copyOctalBaseNumber = octalBaseNumber;
                while (copyOctalBaseNumber != 0) {
                    int remainder = copyOctalBaseNumber % 10;
                    if (remainder >= 8) {
                        printf("Invalid input!\n");
                        isValidOctal = 0;
                        break;
                    }
                    copyOctalBaseNumber /= 10;
                } // end of while loop
                if (!isValidOctal) {
                    break;
                }

                int result = 0;
                while (octalBaseNumber != 0) {
                    int remainder = octalBaseNumber % 10;
                    result = (result << 3) | remainder;
                    octalBaseNumber /= 10;
                }
                int copyResult = result;
                int powerCounter = 0;
                while (copyResult != 0) {
                    copyResult /= 16;
                    ++powerCounter;
                }
                while (powerCounter != 0) {
                    int div = result / pow(16, (--powerCounter));
                    int rem = div % 16;
                    switch (rem) {
                        case 10:
                            printf("A");
                            break;
                        case 11:
                            printf("B");
                            break;
                        case 12:
                            printf("C");
                            break;
                        case 13:
                            printf("D");
                            break;
                        case 14:
                            printf("E");
                            break;
                        case 15:
                            printf("F");
                            break;
                        default:
                            printf("%d", rem);
                    }
                } // end of while loop
                printf("\n");
                break;
            }
            case 2: {
                int isValidBinary = 1;
                printf("Please enter two binary numbers: ");
                unsigned long long a = 0, b = 0;
                int lenA = 0, lenB = 0;
                int printOrder = 0; // 0 - input order 1 - a first 2 - b first
                scanf("%llu %llu", &a, &b);
                unsigned long long copyA = a, copyB = b;

                // Get len of a and b
                while (copyA != 0) {
                    int remainder = copyA % 10;
                    if (remainder >= 2) {
                        printf("Invalid input!\n");
                        isValidBinary = 0;
                        break;
                    }
                    ++lenA;
                    copyA /= 10;
                }

                while (copyB != 0) {
                    int remainder = copyB % 10;
                    if (remainder >= 2) {
                        setbuf(stdout, 0);
                        printf("Invalid input!\n");
                        isValidBinary = 0;
                        break;
                    }
                    ++lenB;
                    copyB /= 10;
                }

                if (!isValidBinary) {
                    break;
                }
                int diff = 0;
                int len = lenA;
                if (lenA > lenB) {
                    diff = lenA - lenB;
                    printOrder = 1;
                    len = lenA;
                } else if (lenA < lenB) {
                    diff = lenB - lenA;
                    printOrder = 2;
                    len = lenB;
                }

                int i;
                for (i = 0; i < diff; ++i) {
                    printf("0");
                }


                switch (printOrder) {
                    case 0:
                    case 1:
                        printf("%d + %d = ", b, a);
                        break;
                    case 2:
                        printf("%d + %d = ", a, b);
                }

                int hasCarry = 0;
                int remainderA = 0, remainderB = 0;

                int sum = 0;
                int j;
                for (j = 0; j < len + 1; ++j) {
                    remainderA = a % 10;
                    remainderB = b % 10;
                    int ans = remainderA ^ remainderB ^ hasCarry;
                    if    ((remainderA && remainderB)
                        || (remainderA && hasCarry)
                        || (remainderB && hasCarry)) {
                        hasCarry = 1;
                    } else {
                        hasCarry = 0;
                    }
                    sum += (ans) ? pow(10, j): 0;
                    a /= 10;
                    b /= 10;
                }
                printf("%d", sum);
                printf("\n");
                break;
            }
            case 3:
            {
                printf("Please enter size: ");
                int x = 0;
                scanf("%d", &x);
                if (x <= 0) {
                    printf("Invalid input!\n");
                    break;
                }
                printf("#");
                int ii;
                for (ii = 0; ii < x; ++ii) {
                    printf("#");
                }
                printf("#");

                int jj;
                if (x == 0) {
                    printf(" ");
                }
                for (jj = 0; jj < x; ++jj) {
                    printf(" ");
                }

                printf("#");
                int kk;
                for (kk = 0; kk < x; ++kk) {
                    printf("#");
                }
                printf("#");

                printf(" ");

                printf("#");
                int mm;
                for (mm = 0; mm < x; ++mm) {
                    printf("#");
                }
                printf("#");

                int ee;
                for (ee = 0; ee < x; ++ee) {
                    printf("\n");
                    printf("#");
                    int gg;
                    for (gg = 0; gg < x; ++gg) {
                        printf("*");
                    }
                    printf("#");
                    int tt;
                    if (x == 0) {
                        printf(" ");
                    }
                    for (tt = 0; tt < x; ++tt) {
                        printf(" ");
                    }

                    printf("#");
                    int yy;
                    for (yy = 0; yy < x; ++yy) {
                        printf("*");
                    }
                    printf("#");

                    printf(" ");

                    printf("#");
                    int rr;
                    for (rr = 0; rr < x; ++rr) {
                        printf("*");
                    }
                    printf("#");
                }

                printf("\n");
                printf("#");
                int ww;
                for (ww = 0; ww < x; ++ww) {
                    printf("*");
                }
                printf("#");
                int uu;
                if (x == 0) {
                    printf("#");
                }
                for (uu = 0; uu < x; ++uu) {
                    printf("#");
                }
                printf("#");
                int qq;
                for (qq = 0; qq < x; ++qq) {
                    printf("*");
                }
                printf("#");
                printf(" ");
                printf("#");
                int ss;
                for (ss = 0; ss < x; ++ss) {
                    printf("*");
                }
                printf("#");
                printf("\n");
                int aa;
                for (aa = 0; aa < x; ++aa) {
                    printf("#");
                    int zz;
                    for (zz = 0; zz < x; ++zz) {
                        printf("*");
                    }
                    printf("*");
                    int dd;
                    for (dd = 0; dd < x; ++dd) {
                        printf("*");
                    }
                    printf("*");
                    int ff;
                    for (ff = 0; ff < x; ++ff) {
                        printf("*");
                    }
                    printf("#");
                    printf(" ");
                    printf("#");
                    int hh;
                    for (hh = 0; hh < x; ++hh) {
                        printf("*");
                    }
                    printf("#");
                    printf("\n");
                }

                printf("#");
                int oo;
                for (oo = 0; oo < x; ++oo) {
                    printf("*");
                }
                printf("#");
                int nn;
                if (x == 0) {
                    printf("#");
                }
                for (nn = 0; nn< x; ++nn) {
                    printf("#");
                }
                printf("#");
                int bb;
                for (bb = 0; bb < x; ++bb) {
                    printf("*");
                }
                printf("#");

                printf(" ");
                printf("#");
                int pp;
                for (pp = 0; pp < x; ++pp) {
                    printf("*");
                }
                printf("#");
                printf("\n");
                int cc;
                for (cc = 0; cc < x; ++cc) {
                    printf("#");
                    int ff;
                    for (ff = 0; ff < x; ++ff) {
                        printf("*");
                    }
                    printf("#");
                    int vv;
                    if (x == 0) {
                        printf(" ");
                    }
                    for (vv = 0; vv < x; ++vv) {
                        printf(" ");
                    }
                    printf("#");
                    int ll;
                    for (ll = 0; ll < x; ++ll) {
                        printf("*");
                    }
                    printf("#");
                    printf(" ");
                    printf("#");
                    int a;
                    for (a = 0; a < x; ++a) {
                        printf("*");
                    }
                    printf("#");
                    printf("\n");
                }

                printf("#");
                int b;
                for (b = 0; b < x; ++b) {
                    printf("#");
                }
                printf("#");
                int c;
                if (x == 0) {
                    printf(" ");
                }
                for (c = 0; c < x; ++c) {
                    printf(" ");
                }
                printf("#");
                int d;
                for (d = 0; d < x; ++d) {
                    printf("#");
                }
                printf("#");
                printf(" ");
                printf("#");
                int e;
                for (e = 0; e < x; ++e) {
                    printf("#");
                }
                printf("#");
                printf("\n");
                break;
            }
            case 4:
            {
                printf("Please enter a binary number: ");
                int binaryNumber;
                scanf("%d", &binaryNumber);
                int copyBinaryNumber = binaryNumber;
                int numOfOnes = 0;
                int isValid = 1;
                while (copyBinaryNumber != 0) {
                    int rem = copyBinaryNumber % 10;
                    if ((rem == 0) || (rem == 1)) {
                        if (rem == 1) {
                            ++numOfOnes;
                        }
                    } else {
                        printf("Invalid input!\n");
                        isValid = 0;
                        break;
                    }
                    copyBinaryNumber /= 10;
                } // end of while loop
                if (isValid) {
                    printf("%d\n", numOfOnes);
                }
                break;
            }
            case 5: {
                printf("Enter a non negative decimal number: ");
                int decimalNumber = 0;
                scanf("%d", &decimalNumber);
                if (decimalNumber < 0) {
                    printf("Invalid input!\n");
                    break;
                }
                int copyDecimalNumber = decimalNumber;
                int counter = 0;
                while (copyDecimalNumber != 0) {
                    copyDecimalNumber /= 2;
                    ++counter;
                }
                printf("%d => ", decimalNumber);
                int copyCounter = counter;
                int i;
                if (decimalNumber == 0) {
                    printf("%d", 0);
                }
                for (i = 0; i < counter; ++i) {
                    int div = decimalNumber / pow(2, (--copyCounter));
                    int rem = div % 2;
                    printf("%d", rem);
                }
                printf("\n");
                break;
            }
            case 6:
            {
                printf("Enter a non negative decimal number: ");
                int decimalNumber = 0;
                scanf("%d", &decimalNumber);
                if (decimalNumber < 0) {
                    printf("Invalid input!\n");
                    break;
                }
                int isZigZag = 1;
                while (decimalNumber != 0) {

                    // 1. get lsb (& 1)
                    // 2. divide by two (remove lsb) x >> 1
                    // 3. save next lsb and compare
                    int lsb = decimalNumber & 1;
                    decimalNumber >>= 1;
                    int nxtLsb = decimalNumber & 1;
                    if (lsb == nxtLsb) {
                        isZigZag = 0;
                        break;
                    }
                } // end of while loop
                if (isZigZag) {
                    printf("true");
                }
                else {
                    printf("false");
                }
                printf("\n");
                break;
            }
            case 7:
                printf("Bye!\n");
                return 0;
            default:
                printf("Invalid option!\n");
                break;
        }
    } // end of while loop
}
