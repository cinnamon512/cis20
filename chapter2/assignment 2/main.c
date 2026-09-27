#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int search(int arr[], int n, int val) {
    for (int i = 0; i < n; i++) {
        if (*(arr + i) == val) {
            return i;
        }
    }
    return -1;
}

void reverse(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {

        int temp = *(arr + i);

        //beginning + i = last element array - i
        *(arr + i) = *((arr + n - 1) - i);

        //last element array is now swapped by beginning + 1
        *((arr + n - 1) - i) = temp;

        //(void *)&arr[0] //memory address
    }
}

void oddFirst(int arr[], int n) {
    //strategy is to put even last
    //when find first even look through rest of array and switch with odd if find it.
    bool swap = true;
    for (int i = 0; i < n && swap; i++) {
        swap = false;
        if (*(arr + i) % 2 == 0) { //checks if even
            //dont swap first element ALERT
            for (int j = i + 1; j < n; j++) {
                if (*(arr + j) % 2 == 1) { //checks if odd
                    //do swap
                    swap = true;
                    //temp = even number
                    int temp = *(arr + i);
                    //lower element = odd
                    *(arr + i) = *(arr + j);
                    //higher element = even
                    *(arr + j) = temp;
                    break;
                }
            }
        }
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(arr + i));
    }
}

int main() {

    int arr[] = {1, 4, 6, 5, 2, 7, 10};

    printf("\nOriginal array: ");
    printArray(arr, 7);

    //Searching Array

    printf("\n\nSearching array for value 6: %d\n", search(arr, 7, 6));

    printf("Searching array for value 8: %d\n\n", search(arr, 7, 8));

    //Reverse Array

    reverse(arr, 7);

    printf("Reversed array: ");
    printArray(arr, 7);

    int arr1[] = {1, 4, 6, 5, 2, 7, 10};


    //Odd First

    printf("\n\nOriginal array: ");
    printArray(arr1, 7);

    printf("\n\nOdd first in array: ");
    oddFirst(arr1, 7);
    printArray(arr1, 7);
    printf("\n");

    return 0;
}
