/*

Merge sort - is a sorting algorithm that follows the divide-and-conquer approach.
It works by recursively dividing the input array into smaller subarrays and sorting
those subarrays then merging them back together to obrain the sorted array.

Time complexity:
- Best Case: O(n log n), when the array is already sorted or nearly sorted.
- Average Case: O(n log n), when the array is randomly ordered.
- Worst Case: O(n log n), when the array is sorted in reverse order.

Space Complexity: O(n), additional space is required for the temprorary array used during merging.

*/

#include <stdio.h>
#include <stdlib.h>


void printArray(int *arr, size_t size);


void merge(int arr[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int *L = (int *)malloc(leftSize * sizeof(int));
    int *R = (int *)malloc(rightSize * sizeof(int));

    for (int i = 0; i < leftSize; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < rightSize; j++)
        R[j] = arr[mid + 1 + j];

    int leftIndex = 0;
    int rightIndex = 0;
    int mergeIndex = left;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (L[leftIndex] <= R[rightIndex]) {
            arr[mergeIndex] = L[leftIndex];
            leftIndex++;
        } else {
            arr[mergeIndex] = R[rightIndex];
            rightIndex++;
        }
        mergeIndex++;
    }

    while (leftIndex < leftSize) {
        arr[mergeIndex] = L[leftIndex];
        leftIndex++;
        mergeIndex++;
    }

    while (rightIndex < rightSize) {
        arr[mergeIndex] = R[rightIndex];
        rightIndex++;
        mergeIndex++;
    }

    free(L);
    free(R);
}


void sort(int arr[], int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;

        sort(arr, left, mid);
        sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


void printArray(int *arr, size_t size)
{
    printf("{");        
    for (int i = 0; i < size; ++i) {
        if (i == size - 1) {
            printf("%d", arr[i]);
            break;
        }
        printf("%d, ", arr[i]);
    }
    printf("}\n");
}


int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    sort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
