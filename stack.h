#ifndef AMFORTH_STACK_H
#define AMFORTH_STACK_H

/**
 * Struct to create a stack
 * 'top' points to the last element in the array 'array'
 * capacity defines the size of 'array'
 */
typedef struct Stack{
    int top;
    unsigned capacity;
    int* array;
} Stack;

/**
 * Creates a a new stack and allocates the memory for it
 * @param capacity Specify the capacity of the stack
 * @return A new element of type Stack*
 */
Stack* createSack(unsigned capacity);

/**
 * Checks if the specified stack is full
 * @param stack The stack which shall be checked
 * @return Returns 0 if the stack is not full and otherwise a non-zero value
 */
int isFull(Stack* stack);

/**
 * Checks if the specified stack is empty
 * @param stack The stack which shall be checked
 * @return Returns 0 if the stack is not empty and otherwise a non-zero value
 */
int isEmpty(Stack* stack);

/**
 * Pushes a new item on top of the stack
 * @param stack Specifies the stack which shall be pushed to
 * @param item Specifies the item which shall be pushed
 * @return Returns INT_MIN if the stack is already full and the item otherwise
 */
int push(Stack* stack, int item);

/**
 * Pops the top element of the stack
 * @param stack Specifies the stack from which shall be popped
 * @return Returns INT_MIN if the stack is empty and the top of the stack item otherwise
 */
int pop(Stack* stack);

/**
 * Returns the last element on the top of the stack without removing it
 * @param stack Specifies the stack
 * @return Returns INT_MIN if the stack is empty and the top of the stack item otherwise
 */
int peek(Stack* stack);

#endif //AMFORTH_STACK_H
