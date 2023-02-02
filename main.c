#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "math.h"

void print_arr(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; ++i) {
        if (i == n - 1) {
            printf("%d", arr[i]);
        } else {
            printf("%d, ", arr[i]);
        }
    }
    printf("]\n");
}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void bubble_sort(int arr[], int n) {
//    int l = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            if (arr[j] > arr[j + 1]) {
//                ++l;
                swap(&arr[j], &arr[j + 1]);
//                printf("After %d swap:\n", l);
//                print_arr(arr, n);
            }
        }
    }
}

int partition(int arr[], int l, int r, int pivot) {
    while (l <= r) {
        while (arr[l] < pivot) {
            ++l;
        }

        while (arr[r] > pivot) {
            --r;
        }

        if (l <= r) {
            swap(&arr[l], &arr[r]);
            ++l;
            --r;
        }
    }
    return l;
}

void quick_sort(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }

    int pivot = arr[(int) ((l + r) / 2)];
    int index = partition(arr, l, r, pivot);
    quick_sort(arr, l, index - 1);
    quick_sort(arr, index, r);
}

//void quick_sort(int arr[], int n) {
//    quick_sort(arr, 0, n - 1);
//}

void merge(int arr[], int start, int middle, int end) {
    int newArr[end - start];
    for (int m = 0; m < end - start; ++m) {
        newArr[m] = 0;
    }

    int i = start, j = middle + 1;
    int k = start;

    while (i < middle - start + 1 && j < end - middle) {
        if (arr[i] <= arr[j]) {
            newArr[k++] = arr[i++];
        } else {
            newArr[k++] = arr[j++];
        }
    }

    while (i <= middle) {
        newArr[k++] = arr[i++];
    }
    while (j <= end) {
        newArr[k++] = arr[j++];
    }


    for (int l = 0; l < end - start; ++l) {
        arr[l] = newArr[l];
    }
}
//    if (i == len1) {
//        while (k < (end - start)) {
//            newArr[k++] = arr[j++];
//        }
//    }
//    if (j == len2) {
//        while (k < (end - start)) {
//            newArr[k++] = arr[i++];
//        }
//    }

void mergesort(int arr[], int start, int end) {
    if (start < end) {
        int middle = (int) (start + end) / 2;
        mergesort(arr, start, middle);
        mergesort(arr, middle + 1, end);
        merge(arr, start, middle, end);
    }
}

int min(int arr[], int n) {
    if (n == 1) {
        return arr[0];
    }

    int newMin = min(arr + 1, n - 1);

    if (arr[0] < newMin) {
        return arr[0];
    }
    else {
        return newMin;
    }
}

// backtracking problem
int isSum(int arr[], int n, int x) {
    if (x == 0) {
        return -1;
    }
    if (n == 1) {
        return arr[0] == x ? 1: -1;
    }

    int lol = isSum(arr + 1, n - 1, x - arr[0]);
    int lmao =  isSum(arr + 1, n - 1, x);
    if (lol) {
        return lol + 1;
    }
    else if (lmao) {
        return lmao + 1;
    }
}

int subsum2(int a[], int n, int x) {
    if (x==0) return 0;
    if (n<=0) return -1;

    if (a[0] <=x) {
        int k = subsum2(a + 1, n - 1, x-a[0]);
        if (k> - 1) return k + 1;
    }
    return subsum2(a + 1, n- 1, x);
}

//int checkEqualSubString(char* str1, char* str2) {
//    if (!strlen(str2)) return TRUE;
//    if (!strlen(str1)) return FALSE;
//    if (*str2 != *str1) return FALSE;
//    return checkEqualSubString(str1 + 1, str2 + 1);
//}
//int isSubString(char* str1, char* str2) {
//    if (!str2 || !strlen(str2)) return TRUE;
//    if (!str1 || !strlen(str1)) return FALSE;
//    if (checkEqualSubString(str1, str2) == TRUE)
//        return TRUE;
//    else
//        return isSubString(str1 + 1, str2);
//}

int string2num(char* str) {
    if (str[1] == '\0') {
        return (int) str[0] - '0';
    }
    return (((int)(str[0] - '0')) * (pow(10, strlen(str) - 1))) + string2num(str + 1);
}

int string2numIterative(char* str) {
    int lenStr = strlen(str);
    int num = 0;
    int step = 0;
    while (str[step] != '\0') {
        num += (str[step] - '0') * pow(10, (lenStr - (step++) - 1));

    }
    return num;
}

int diffArray(int arr1[], int arr2[], int n, int x) {
    if (n == 1) {
        return arr2[0] - arr1[0] == x;
    }

    return diffArray(arr1 + 1, arr2 + 1, n - 1, x-(arr2[0] - arr1[0]));
}

int maxNum(int x, int y) {
    return (x > y) ? x: y;
}

// knapsack problem
int optimizeGemstone(int volume[], int worth[], int number, int max) {
    if (number == 0) {
        return 0;
    }
    if (max == 0) {
        return 0;
    }

    if (max - volume[0] >= 0) {
        return maxNum(optimizeGemstone(volume + 1, worth + 1, number - 1, max - volume[0]) + worth[0],
                      optimizeGemstone(volume + 1, worth + 1, number - 1, max));
    }
    else {
        return  optimizeGemstone(volume + 1, worth + 1, number - 1, max);
    }
}
int main() {
    int vol[] = {2, 4, 1, 3};
    int wrth[] = {12, 5, 4, 7};
    int m = 5;
    int l = 4;
    printf("%d", optimizeGemstone(vol, wrth, l, m));
//    printf("%d", 'a' == 'o');
//    char str[] = "Shmulik Kipod";
//    char str2[] = "Kipod Shmulik";
//    char* arr[] = {str, str2, str+1, str};
//    char str3[] = "mulik Kipod";
//    printf("%ld\n", sizeof(arr[3]));
//    printf("%ld %ld %ld\n", sizeof(arr), sizeof(str2), sizeof(arr[3]));
    return 0;
}
