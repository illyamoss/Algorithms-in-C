/*

Merge sort - is a sorting algorithm that follows the divide-and-conquer approach.
It works by recursively dividing the input array into smaller subarrays and sorting
those subarrays then merging them back together to obrain the sorted array.

Time complexity:
- Best Case: O(n log n), when the array is already sorted or nearly sorted.
- Average Case: O(n log n), when the array is randomly ordered.
- Worst Case: O(n log n), when the array is sorted in reverse order.

Space Complexity: O(n), additional space is required for the temprorary array used during merging.

Advantages:
- Stability: Merge sort is a stable sorting algorithm, which means it maintains
  the relative order of equal elements in the input array.
- Guaranteed worst-case performacne: Merge-sort has a worst-case time complexity
  of O(N log N), which means it performs well even on large datasets.
- Simple to impolement: the divide-and-conquer approach is straightformward.
- Naturally Parallel: We independently merge subarrays that makes it suitable
  for parallel processing.

Disadvantages:
- Space complexity: MS requires additional memory to store
  merged sub-arrays during the sorting process.
- Not in-place: Merge sort is not an in-place sorting algorithm,
  which means it requires additional memory to store the sorted data.
  This can be a disadvantage in applications where memory usage is a concern.
- Slower than QuickSort in general. QuickSort is more cache friendly because
  it works in place.

Merge sort vs QuickSort:
Quick sort is typically faster than merge sort when the data is stored in memory.
However, when the data set is huge and is stored on external devices such as a hard
drive, merge sort is the clear winner in terms of speed. It minimizes the expensive
reads of the external drive and also lends itself well to parallel computing.

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
