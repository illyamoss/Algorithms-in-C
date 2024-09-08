/*

A Heap - is a complete binary tree data structure that satisfies the heap property:
for every node, the value of its children is greater than or equal to its own value.
Heaps are usually used to implement priority queues, where the smallest (or largest)
element is always at the root of the tree.

In a heap the value of each node is compared to the values of its children in a
specific way:

- Max-Heap: The value of each node is greater than or equal to the values of its
  children, ensuring that the root node contains the max value. As you move down the,
  the value decreases.

- Min-Heap: The value of each node is less than or equal to the values of its children,
  ensuring that the root node contains the min value. As you move down the tree the
  values increase.


Heap Operations:

- Insert
- Extract Max/Min
- Heapify: Converts an arbitrary binary tree into a heap.


Heap Data Structure Applications:

- Priority queues, where elements are retrieved based on their priority(max or min value).
- Heapsort: sorting algo that uses a heap to sort an array.
- Dijkstra's algo and Prim's algo for finding the shortest paths and minimum spanning trees.


- Left chlid: 2 * i + 1
- Right child: 2 * i + 2
- Parent: (i - 1) / 2

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100


typedef struct Heap {
    int size;
    int capacity;
    int *arr;
} Heap;


Heap *createHeap(size_t capacity)
{
    Heap *newHeap = (Heap *)malloc(sizeof(Heap));
    if (newHeap == NULL) {
        printf("Allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int *newArr = (int *)malloc(capacity * sizeof(int));
    if (newArr == NULL) {
        printf("Allocation failed\n");
        free(newHeap);
        exit(EXIT_FAILURE);
    }

    newHeap->arr = newArr;
    newHeap->size = 0;
    newHeap->capacity = capacity;

    return newHeap;
}


void swap(int *x, int *y)
{
    int temp = *y;
    *y = *x;
    *x = temp;
}


void heapify(Heap *heap, int index)
{
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->arr[left] > heap->arr[largest])
        largest = left;
    if (right < heap->size && heap->arr[right] > heap->arr[largest])
        largest = right;
    
    if (largest != index) {
        swap(&heap->arr[index], &heap->arr[largest]);
        heapify(heap, largest);
    }
}


void insert(Heap *heap, int value)
{
    if (heap->size == heap->capacity) {
        printf("Heap overflow!\n");
        return;
    }

    heap->size++;
    int index = heap->size - 1;
    heap->arr[index] = value;

    while (index != 0 && heap->arr[(index - 1) / 2] < heap->arr[index]) {
        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}


int extractMax(Heap* heap) {
    if (heap->size <= 0)
        return -1;
    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    heapify(heap, 0);

    return root;
}


void deleteKey(Heap* heap, int index) {
    if (index < 0 || index >= heap->size) {
        printf("Index out of bounds.\n");
        return;
    }

    heap->arr[index] = __INT_MAX__;
    while (index != 0 && heap->arr[(index - 1) / 2] < heap->arr[index]) {
        swap(&heap->arr[index], &heap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }

    extractMax(heap);
}


void printHeap(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}


int main()
{
    Heap *heap = createHeap(MAX_SIZE);

    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 40);
    insert(heap, 50);
    insert(heap, 69);

    printf("Heap elements:\n");
    printHeap(heap);

    printf("Extracting max: %d\n", extractMax(heap));

    printf("Heap after extracting max:\n");
    printHeap(heap);

    deleteKey(heap, 3);
    printf("Heap after deleting key at index 3:\n");
    printHeap(heap);

    return 0;
}
