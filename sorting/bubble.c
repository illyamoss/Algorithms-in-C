/* 
Bubble sort - the simpliest sorting algorithm that works by repeatedly
swapping the adjacent elements if they are in the wrong order. This
algorithm is not suitable for large data sets as its average and 
worst-case time complexity is quite high.

In bubble sort algorithm,
- traverse from left and compare adjacent elements and the higher one is placed at right side.
- in this way, the largest element is moved to the rightmost end at first.
- This process is then continued to find the second largest and place it and so on until data is sorted.


*/

#include <stdio.h>


int main(void)
{
    int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
    size_t size = sizeof(arr) / sizeof(int);

    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }

    printf("{");        
    for (int i = 0; i < size; ++i) {
        if (i == size - 1) {
            printf("%d", arr[i]);
            break;
        }
        printf("%d, ", arr[i]);
    }
    printf("}\n");
        
    return 0;
}
