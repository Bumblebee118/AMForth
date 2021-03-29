#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* createSack(unsigned capacity){
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(Stack* stack){
    return stack->top == stack->capacity -1;
}

int isEmpty(Stack* stack){
    return stack->top == -1;
}

int push(Stack* stack, int item){
    if(isFull(stack)){
        return INT_MIN;
    }
    return stack->array[++stack->top] = item;
}

int pop(Stack* stack){
    if(isEmpty(stack)){
        return INT_MIN;
    }

    return stack->array[stack->top--];
}

int peek(Stack* stack){
    if(isEmpty(stack)){
        return INT_MIN;
    }

    return stack->array[stack->top];
}

