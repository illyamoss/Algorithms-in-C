#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX 100


typedef struct Stack {
    int top;
    int arr[MAX];
} Stack;


void initStack(Stack* stack)
{
    stack->top = -1; 
}


bool isFull(Stack* stack)
{
    return stack->top == (MAX - 1);    
}


bool isEmpty(Stack* stack)
{
    return stack->top == -1;
}


void add(Stack* stack, int data)
{
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }

    stack->arr[++(stack->top)] = data;
}


int pop(Stack* stack)
{
    if (isEmpty(stack)) {
        printf("Stack underflow\n"); 
        return -1;
    }

    return stack->arr[(stack->top)--];
}


int peek(Stack* stack)
{
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }

    return stack->arr[stack->top];
}


int main(void)
{
    Stack stack;
    initStack(&stack);

    for (int i = 0; i < 100; ++i) {
        add(&stack, i);
    }
    
    for (int i = 0; i < 100; ++i) {
        printf("Pop: %d\n", pop(&stack));
    }

    printf("Data: %d\n", stack.arr[28]);
    // printf("Peek: %d\n", peek(&stack));
    
    // printf("Pop: %d\n", pop(&stack));
    // printf("Pop: %d\n", pop(&stack)); 

    return 0;
}
