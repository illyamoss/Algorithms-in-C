/*

Radix sort - linear sorting algorithm that sorts elements by processing them
digit by digit. It is an efficient sorting algorithm for integers or strings
with fixed-size keys.

The key idea behind Radix Sort is to exploit the concept of place value.
It assumes that sorting numbers digit by digit will eventually result in a
fully sorted list. Radix Sort can be performed using different variations,
such as Least Significant Digit (LSD) Radix Sort or Most Significant Digit
(MSD) Radix Sort.


How does it work?
1. Choose a Base: Typically, the base is 10 for decimal numbers.
2. Sort by Each Digit: The numbers are grouped (or "bucketed")  based on each digit,
   starting from the LSD (rightmost digit).
3. Stable Sort Within Each Digit: A stable sorting algorithm (like Counting Sort) is
   applied to sort numbers by the current digit.
4. Repeat for Next Digit: Move to the next more significant digit and repeat the sorting
   process.
5. Final Sorted Array: Once the MSD is processed, the array is fully sorted.

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int max(int arr[], int n)
{
    int result = arr[0];
    for (int i = 0; i < n; i++) {
        if (result < arr[i])
            result = arr[i];
    }
    return result;
}


void countingSort(int arr[], int n, int exp)
{
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void sort(int arr[], int n)
{
    int maximum = max(arr, n);

    for (int exp = 1; maximum / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
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
    int arr[134];

    srand(time(NULL));

    int i = 0;
    while (i < 134) {
        int min = 50;
        int max = 450;

        int randomNumber = min + (rand() % (max - min + 1));
        arr[i] = randomNumber;
        i++;
    }

    int n = sizeof(arr) / sizeof(int);

    printf("Unsorted: \n");
    printArray(arr, n);
    sort(arr, n);

    printf("Sorted: \n");
    printArray(arr, n);

    return 0;
}
