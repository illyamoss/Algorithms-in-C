#include <stdio.h>

#define SIZE 5


void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d\n", arr[i]);    
    }
}

int main(void)
{
    int arr[SIZE] = {1, 2, 3, 4, 5};
    
    printArray(arr, SIZE);

    return 0;
}

