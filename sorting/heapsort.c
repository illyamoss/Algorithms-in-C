/*

Heapsort - a comparison based sorting algorithm based on Binary Heap Data Structure.
That is often described as "A selection sorting implementation but with the right data structure".

It can be seen as an optimization over selection sort where we first find the max (or min) element
and swap it with the last (or first). We repeat the same process for the remaining elements.
In heap sort, we use binary heap so that we can quickly find and move the max element (in O(log n)
instead of O(n)) and hence achieve the O(n log n) time complexity.


Time Complexity: O(n log n)
Auxiliary space: O(log n), due to the recursive call stack.
    However, auxiliary space can be O(1) for iterative implementation.


Important points about Heap Sort:
- Heap Sort is an in-place algorithm
- Its typical implementation is not stable but can be made stable.
- Typically 2-3 times slower than well-implemented QuickSort.
  The reason for slowness is a lack of locality of reference.


Advantages of Heap Sort:
- Efficient Time Complexity: Heap Sort has a time complexity of O(n log n) in all
  cases. This makes it efficient for sorting large datasets. The log n factor comes
  from the height of the binary heap, and it ensures that the algo maintains good
  performance even with a large number of elements.

- Memory usage: Memory usage can be minimal (by writing an iterative heapify() 
  instead of a recursive one). So apart from what is necessary to hold the 
  initial list of items to be sorted, it needs no additional memory space to work.

- Simplixity: it is simpler to understand than other equally efficient sorting
  algorithms because it does not use advanced computer science concepts such as
  recursion.


Disadvantages of Heap Sort:
- Costly: heap sort is costly as the constants are higher compared to merge sort
  even if the time complexity if O(n log n) for both.

- Unstable: heap sort is unstable. It might rearrange the relative order.

- Inefficient: heap sort is not very efficient because of the constants in the 
  time complexity.

*/

#include <stdio.h>

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


void heapify(int *arr, size_t size, int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left] > arr[largest])
        largest = left;
    if (right < size && arr[right] > arr[largest])
        largest = right;
    
    if (largest != index) {
        swap(&arr[largest], &arr[index]);
        heapify(arr, size, largest);
    }
}


void heapSort(int *arr, size_t size)
{
    for (int index = size / 2 - 1; index >= 0; index--)
        heapify(arr, size, index);

    for (int index = size - 1; index >= 0; index--) {
        swap(&arr[0], &arr[index]);
        heapify(arr, index, 0);
    }
}


void printArray(int *arr, size_t size)
{
    for (int index = 0; index < size; index++)
        printf("%d ", arr[index]);
    printf("\n");
}


int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    printArray(arr, size);

    heapSort(arr, size);

    printArray(arr, size);

    return 0;
}
