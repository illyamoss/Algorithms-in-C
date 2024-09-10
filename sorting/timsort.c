/*

Tim Sort - a hybrid, stable sorting algorithm, derived from merge sort and insertion sort,
    designed to perform well on many kinds of real-world data. It was implemented by Tim
    Peters in 2002 for use in the Python programming language.


The main idea behind Tim Sort is to exploit the existing order in the data to minimize the
number of comparisons and swaps. It achieves this by dividing the array into small subarrays
called runs, which are already sorted, and then merging these runs using a modified merge
sort algorithm.


How does Timsort work?
1. Define the n of the run
- Minimum run n: 32

2. Divide the array into runs
- In this step, we'll use insertion sort to sort the small subsequences (runs) within array.
- The initial array: [4, 2, 8, 6, 1, 5, 9, 3, 7]
- No initial runs are present, so we'll create runs using insertion sort.
- Sorted runs: [2, 4], [6, 8], [1, 5, 9], [3, 7]
- Updated array: [2, 4, 6, 8, 1, 5, 9, 3, 7]

3. Merge the runs
- In this step, we'll merge the sorted runs using amodified merge sort algorithm.
- Merge the runs until the entire array is sorted.
- Merged runs: [2, 4, 6, 8], [1, 3, 5, 7, 9]
- Updated array: [2, 4, 6, 8, 1, 3, 5, 7, 9]

4. Adjust the run n
- After each merge operation, we double the n of the run until it exceeds the length of the array.
- The run n doubles: 32, 64, 128

5. Continue merging
- Repeat the merging process until the entire array is sorted
- Final merged run: [1, 2, 3, 4, 5, 6, 7, 8, 9]

The final sorted array is [1, 2, 3, 4, 5, 6, 7, 8, 9]


Complexity Analysis:
-Best case: O(n)
-Average case: O(n*log(n))
-Worst case: O(n*log(n))
-Space: O(n)
-Stable: YES
-In-Place sorting: NO, as it requires extra space.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUN 32


void insertionSort(int arr[], int left, int right)
{
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}


void merge(int arr[], int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int *L = (int *)malloc(leftSize * sizeof(int));
    int *R = (int *)malloc(rightSize * sizeof(int));

    for (int i = 0; i < leftSize; i++)
        L[i] = arr[left + i];

    for (int i = 0; i < rightSize; i++)
        R[i] = arr[mid + i + 1];

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
        mergeIndex++;
        leftIndex++;
    }

    while (rightIndex < rightSize) {
        arr[mergeIndex] = R[rightIndex];
        mergeIndex++;
        rightIndex++;
    }

    free(L);
    free(R);
}

void timSort(int arr[], int n)
{
    // Sort individual subarrays of n RUN using Insertion Sort
    for (int index = 0; index < n; index += RUN) {
        insertionSort(
            arr,
            index, 
            (index + RUN - 1 < n) ? (index + RUN - 1) : (n - 1)
        );
    }

    // Start merging subarrays
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n) ? (left + 2 * size - 1) : (n - 1);

            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}


void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d\n", arr[i]);
    printf("\n");
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
    timSort(arr, n);

    printf("Sorted: \n");
    printArray(arr, n);

    return 0;
}
