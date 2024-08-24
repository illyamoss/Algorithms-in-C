#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX 100


typedef struct CircularQueue {
    int front;
    int rear;
    int arr[MAX];
} CircularQueue;


void init(CircularQueue* queue)
{
    queue->front = -1; 
    queue->rear = -1;
}


bool isEmpty(CircularQueue* queue)
{
    return queue->front == -1;
}


bool isFull(CircularQueue* queue)
{
    return (queue->rear + 1) % MAX == queue->front;
}


void enqueue(CircularQueue* queue, int value)
{
    if (isFull(queue)) {
        printf("CircularQueue overflow\n");
        return;
    }

    if (queue->front == -1) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % MAX;
    queue->arr[queue->rear] = value;

    // printf("Value: %d, rear: %d\n", value, queue->rear);
}


int dequeue(CircularQueue* queue)
{
    if (isEmpty(queue)) {
        printf("CircularQueue underflow\n");
        return -1;
    }

    int data = queue->arr[queue->front];

    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX;
    }

    return data;
}


int peek(CircularQueue* queue)
{
    if (isEmpty(queue)) {
        printf("CircularQueue underflow\n");
        return -1;
    }
    return queue->arr[queue->front];
}


int main(int argc, char* argv[])
{
    // argc - number of arguments
    // argv - array of C-style strings representing the arguments

    CircularQueue queue;
    init(&queue);
    
    for (int i = 0; i < 10; ++i) {
        enqueue(&queue, i);
    }  

    printf("Peek: %d\n", peek(&queue));

    for (int i = 0; i < 50; ++i) {
        printf("Dequeue: %d\n", dequeue(&queue));
    }
    
    for (int i = 0; i < 50; ++i) {
        enqueue(&queue, i);
    }

    printf("Peek: %d\n", peek(&queue));

    for (int i = 0; i < 50; ++i) {
        printf("Dequeue: %d\n", dequeue(&queue));
    }

    return 0;
}
