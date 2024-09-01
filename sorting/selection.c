/*

Selection sort - simple and efficient sorting algorithm that works by repeatedly selecting the smallest (or largest)
element from the unsorted poriton of the list and moving it to the sorted portion of the list.

*/

#include <stdio.h>
#include <math.h>


void swap(int *pX, int *pY)
{
    int temp = *pY;
    *pY = *pX;
    *pX = temp;
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


void sort(int arr[], size_t size)
{
    for (int i = 0; i < size; ++i) {
        // find the smallest
        int *smallest = NULL;
        for (int j = i; j < size; ++j) {
            if (smallest == NULL || arr[j] < *smallest)
                smallest = &arr[j];
        }
        if (arr[i] > *smallest) {
            swap(&arr[i], smallest);
        }
    }
}


int main()
{
    int arr[] = {7, 6, 5, 4, 3, 2, 1, 435645, 346, 13246, 346, 2346, 6346, 62346};
    size_t size = sizeof(arr) / sizeof(int);

    sort(arr, size);

    printArray(arr, size);

    return 0;
}
