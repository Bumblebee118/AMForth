#include <limits.h>
#include <stdlib.h>
#include "stack.h"

//mallocs memory to create a new stack with the given capacity
Stack *createStack(unsigned capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *) malloc(stack->capacity * sizeof(int));
    return stack;
}

//returns true if the stack is full
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

//returns true if the stack is empty
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

//pushes a new element on the top of the stack
int push(Stack *stack, int item) {
    if (isFull(stack)) {
        return INT_MIN;
    }
    return stack->array[++stack->top] = item;
}

//pops the top of the stack
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }

    return stack->array[stack->top--];
}

//returns the top element of the stack without modifying the stack
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        return INT_MIN;
    }

    return stack->array[stack->top];
}

