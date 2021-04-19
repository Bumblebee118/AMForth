#include "global.h"
#include "error.h"

//mallocs memory to create a new stack with the given capacity
Stack *createStack(unsigned capacity) {
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (cell_t *) malloc(stack->capacity * sizeof(cell_t));
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
cell_t push(Stack *stack, cell_t item) {
    if (isFull(stack)) {
        return LONG_MIN;
    }
    return stack->array[++stack->top] = item;
}

//pops the top of the stack
cell_t pop(Stack *stack) {
    if (isEmpty(stack)) {
        ERROR("Stack underflow");
        return LONG_MIN;
    }

    return stack->array[stack->top--];
}

//returns the top element of the stack without modifying the stack
cell_t peek(Stack *stack) {
    if (isEmpty(stack)) {
        ERROR("Stack underflow");
        return LONG_MIN;
    }

    return stack->array[stack->top];
}

void clearStack(Stack *stack) {
    stack->top = -1;
}

void deleteStack(Stack *stack) {
    if (stack != NULL) {
        free(stack->array);
        free(stack);
    }
}

int numberOfElements(Stack *stack) {
    return (stack->top + 1);
}

