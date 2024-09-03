/*

Insertion sort - sipmle sorting algorithm that works by iteratively inserting each element
of an unsorted list into its correct position in a sorted portion of the list. It is a stable
sorting algorithm, meaning that elements with equal values maintain their relative order in the sorted output.

Time Complexity: O(n^2)
Space Complexity: O(1)

*/

#include <stdio.h>


void sort(int *arr, size_t size)
{
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {   
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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
    int arr[] = {43, 54, 32};
    size_t size = sizeof(arr) / sizeof(int);

    sort(arr, size);
    printArray(arr, size);

    return 0;
}
