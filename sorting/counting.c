/*

Counting Sort - non-comparison-based sorting algorithm. It's particularly efficient
    when the range of input values is small compared to the number of elements to be
    sorted. The basic idea behind Counting Sort is to count the frequency of each
    distinct element in the input array and use that information to place the
    elements in their correct sorted positions.


How does it work?

inputArray[] = 2, 5, 3, 0, 2, 3, 0, 3
max = 5

1. Find out the max element from the given array.
2. Initialize a countArray[] of lenght max+1 with all elements as 0. This will be used
   for storing the occurrences of the elements of the input array.
3.
   - In the countArray[], store the count of each unique element of the input array
     at their respective indices.
   - For Example: The count of element 2 in the input array is 2. So, store 2 at index
     2 in the count in the count array. Similarly, the count element 5 in the input
     array is 1, hence store 1 at index 5 in the countArray[].
    
4. Store the cumulative sum or prefix sum of the elements of the countArray[] by doing
   countArray[i] = countArray[i - 1] + countArray[i]. This will help in placing the 
   elements of the input array at the correct index in the output array.

5. Iterate from end of the input array and because traversing input array from end preserves
   the order of equal elements, which eventually makes this soring algorithm stable.


Counting sort is a simple, efficient sorting algorithm used to sort a collection of
non-negative integers. Here's how it works, step-by-step:

### 1. **Understand the range**:
   Counting sort works best when the numbers in the list have a relatively small range
   (e.g., between 0 and 100). The algorithm relies on knowing the minimum and maximum
   values in the list.

### 2. **Create a count array**:
   - First, you create an array called the **count array**. The size of this array is
   the largest number in the input list plus one.
   - Each index in this count array corresponds to a value in the input list, and it
   will store how many times each value appears in the list.

### 3. **Count the occurrences**:
   - For each number in the input list, you increment the value at the corresponding
   index in the count array. For example, if the number `3` appears twice in the input
   list, you'll increment the count array at index 3 by 2.

### 4. **Modify the count array** (Optional for some versions):
   - Sometimes, you modify the count array to store the cumulative count, which helps
   place the numbers in their correct positions when creating the sorted output.

### 5. **Create the sorted list**:
   - Using the count array, you can now generate the sorted list by repeating each number
   according to its count and placing it in the output array.

### Example:
If you want to sort the list `[4, 2, 2, 8, 3, 3, 1]`:

1. The maximum value is `8`, so you create a count array with 9 elements (from 0 to 8).
2. Count the occurrences of each number:
   ```
   Count array: [0, 1, 2, 2, 1, 0, 0, 0, 1]
   ```
   - There is 1 occurrence of `1`, 2 occurrences of `2`, etc.
3. Use the count array to generate the sorted list:
   ```
   Sorted list: [1, 2, 2, 3, 3, 4, 8]
   ```

Counting sort is **efficient** for small ranges of integers because it runs in
linear time, O(n + k), where `n` is the number of elements and `k` is the range of
input values.

Time complexity is:

𝑂(𝑛+𝑘)

where:

n is the number of elements in the input list.
k is the range of the input values (i.e., max value - min value + 1).
Space Complexity:
Counting Sort uses additional space for the count array and the output array.

Count array: This takes O(k) space, where k is the range of input values.
Output array: This takes O(n) space, as we need an array of the same size as the input list to store the sorted elements.
Thus, the overall space complexity is:

𝑂(𝑛+𝑘)


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printArray(int arr[], int n);


int max(int arr[], int n)
{
    int result = arr[0];
    for (int i = 0; i < n; i++) {
        if (result < arr[i])
            result = arr[i];
    }
    return result;
}


void sort(int arr[], int n)
{
    int maximum = max(arr, n);
    int countArray[maximum + 1];

    for (int i = 0; i <= maximum; i++) {
        countArray[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int number = arr[i];
        countArray[number]++;
    }

    int arrIndex = 0;
    for (int i = 0; i <= maximum; i++) {
        while (countArray[i] > 0) {
            arr[arrIndex] = i;
            arrIndex++;
            countArray[i]--;
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
    sort(arr, n);

    printf("Sorted: \n");
    printArray(arr, n);

    return 0;
}
