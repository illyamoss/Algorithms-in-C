/*

Bucket sort - is a sorting technique that involves dividing elements into various
groups, or buckets. These buckets are formed by uniformly distributing the elements.
Once the elements are divided into buckets, they can be sorted using any other
sorting algorithm. Finally, the sorted elements are gathered  together in an ordered
fashion.


Use cases:
1. Uniformly Distributed Data: Efficient for data that is uniformly distributed
   accross a known range.
2. Sorting Flaot Numbers: Often used for sorting floating-point numbers in the
   range [0, 1] by scaling them to integers.


Complexity analysis:
1. Time Complexity:
   - Average Case: O(n + k), where n is the number of elements and k is the number
     of buckets. If the elements are uniformly distributed and buckets are of similar
     size, sorting within each bucket becomes efficient.
   - Worst Case: O(n^2): which can occur if all elements end up in a single bucket,
     requiring a sort operation on the entire array.
2. Space Complexity:
   - Auxiliary space: O(n + k). Space is required for the buckets and the output array.


Advantages:
- Adaptive: Works well with uniformly distributed data and can be very efficient with
  a good bucket distribution strategy.
- Parallelizable: Sorting within buckets can be done in parallel, potentially
  increasing efficiency.


Disadvantages:
- Not suitable for all data distributions: Performance degrades if the data is not
  uniformly distributed, leading to inefficient sorting if many elements fall into
  a few buckets.
- Space complexity: requires additional space proportional to the number of buckets and
  elements.

*/

#include <stdio.h>
#include <stdlib.h>


#define BUCKET_SIZE 10
#define ARRAY_SIZE 10


void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


void bucketSort(float arr[], int n)
{
    int buckets[BUCKET_SIZE][ARRAY_SIZE];
    int bucketCount[BUCKET_SIZE] = {0};

    for (int i = 0; i < n; i++) {
        int bucketIndex = arr[i] * BUCKET_SIZE;
        buckets[bucketIndex][bucketCount[bucketIndex]] = arr[i] * 100; // Scale to integer for counting sort
        bucketCount[bucketIndex]++;
    }
    
    // Sort individual buckets using insertion sort
    for (int i = 0; i < BUCKET_SIZE; i++) {
        if (bucketCount[i] > 0) {
            insertionSort(buckets[i], bucketCount[i]);
        }
    }

    // Concatenate: Combine all sorted buckets into original array
    int index = 0;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        for (int j = 0; j < bucketCount[i]; j++) {
            arr[index++] = buckets[i][j] / 100.0; // Scale back to float
        }
    }
}


int main() {
    // Input array
    float arr[ARRAY_SIZE] = {0.42, 0.32, 0.23, 0.52, 0.5, 0.31, 0.22, 0.73, 0.25, 0.12};
    int n = ARRAY_SIZE;

    // Print the array before sorting
    printf("Unsorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");

    // Perform bucket sort
    bucketSort(arr, n);

    // Print the array after sorting
    printf("Sorted array: \n");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }
    printf("\n");

    return 0;
}
