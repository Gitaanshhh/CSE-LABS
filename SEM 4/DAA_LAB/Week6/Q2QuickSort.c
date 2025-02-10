/*
2) Sort given set of integers using Quick sort and analyze its efficiency.
Obtain the experimental result of order of growth and plot the result.
*/

#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low]; // Pivot is the smallest element (first element)
    int i = low;

    for (int j = low + 1; j <= high; j++)
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    swap(&arr[i], &arr[low]); // Place pivot in the correct position
    return i;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original Array: \n");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);

    printf("Sorted Array: \n");
    printArray(arr, n);

    return 0;
}