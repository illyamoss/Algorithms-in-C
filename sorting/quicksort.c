/*

Quicksort - non stable sorting algorithm that uses divide-and-conquer
strategy to sort an array.
It does so by selecting a pivot element, and then sorting values larger
than it on one side and smaller to the other side, and then it repeats
those steps until the array is sorted.
It's useful for sorting big data sets.


How does it work?

1) Choose a pivot
2) Partition the array around pivot. After partition, it is ensured that
all elements are smaller than all right and we got index of the end point
of smaller elements. The left and right may not be sorted individually.
3) Recursively call for the two partitioned left and right subarrays.
4) We stop recursion when there is only one element left.


Choose of pivot:

There are many different choices for picking pivots.

- Always pick the first (or last) element as a pivot. The
  problem with this approach is it ends up in the worst case
  when array is already sorted.

- Pick a random element as a pivot. This is a preferred approach
  because it does not have a pattern for which the worst case
  happens.

- Pick the median element as a pivot. This is an ideal approach in
  terms of time complexity as we can find median in linear time and
  the partition function will always divide the input array into two
  halves. But it is low on average as median finding has high constants.


Partition Algo:

The key process in quickSort is a partition(). There are three
common algorithms to partition. All these algos have O(n) time
complexity.

1) Naive Partition: Here we create a copy of the array. First put
   all smaller elements and then all greater. Finally we copy
   the temporary array back to the original array. This requires
   O(n) extra space.

2) Lomuto Partition: This is a simple algorithm, we keep track
   of index of smaller elements and keep swapping.

3) Hoare's Partition: This is the fastest of all. Here we traverse
   array from both sides and keep swapping greater element on left
   with smaller elements on right while the array is not partitioned.


Time complexity:
- Bast Case: O(n log n)
- Average Case: O(n log n)
- Worst case: O(n^2)
- Auxiliary space: O(1), if we don't consider the recursive stack space.
  If we consider the recursive stack space then, in the worst case 
  quicksort could make O(n).


Advantages:
- It is a divide-and-conquer algo that makes it easier to solve problems.
- It is efficient on large data sets.
- It has a low overhead, as it only requires a small amount of memory to function.
- It is cache friendly as we work on the same array to sort and do not copy data to any auxiliary memory blocks.
- It is tail recursive and hence all the tail call oprimization can be done.


Disadvantages:
- It has a worst-case complexity of O(n^2), which occurs when the pivot is chosen poorly.
- It is not a good option for small data sets.
- It is not a stable sort, meaning that if two elements have the same key, their relative
  order will not be preserved in the sorted output in case of quicksort, because here we
  are swapping elements according to the pivot's position (without considering their 
  original positions).

*/

#include <stdio.h>
#include <stdlib.h>


void swap(int *x, int *y)
{
    int temp = *y;
    *y = *x;
    *x = temp;
}


int partition(int arr[], int low, int high)
{
    int pivot = arr[high];

    int currentIndex = low - 1;

    for (int swapMarker = low; swapMarker <= high - 1; ++swapMarker) {
        if (arr[swapMarker] < pivot) {
            ++currentIndex;
            swap(&arr[currentIndex], &arr[swapMarker]);
        }
    }

    swap(&arr[currentIndex + 1], &arr[high]);
    return currentIndex + 1;
}


void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int partitionIndex = partition(arr, low, high);

        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
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

    quickSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
