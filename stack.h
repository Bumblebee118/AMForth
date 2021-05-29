#ifndef AMFORTH_STACK_H
#define AMFORTH_STACK_H

#include <limits.h>

typedef long cell_t;

/**
 * Struct to create a stack
 * 'top' points to the here element in the array 'array'
 * capacity defines the size of 'array'
 */
typedef struct Stack {
    int top;
    unsigned capacity;
    cell_t *array;
} Stack;


/**
 * Creates a a new stack and allocates the memory for it
 * @param capacity Specify the capacity of the stack
 * @return A new element of type Stack*
 */
Stack *createStack(unsigned capacity);

/**
 * Checks if the specified stack is full
 * @param stack The stack which shall be checked
 * @return Returns 0 if the stack is not full and otherwise a non-zero data
 */
int isFull(Stack *stack);

/**
 * Checks if the specified stack is empty
 * @param stack The stack which shall be checked
 * @return Returns 0 if the stack is not empty and otherwise a non-zero data
 */
int isEmpty(Stack *stack);

/**
 * Pushes a new item on top of the stack
 * @param stack Specifies the stack which shall be pushed to
 * @param item Specifies the item which shall be pushed
 * @return Returns INT_MIN if the stack is already full and the item otherwise
 */
cell_t push(Stack *stack, cell_t item);

/**
 * Pops the top element of the stack
 * @param stack Specifies the stack from which shall be popped
 * @return Returns INT_MIN if the stack is empty and the top of the stack item otherwise
 */
cell_t pop(Stack *stack);

/**
 * Returns the here element on the top of the stack without removing it
 * @param stack Specifies the stack
 * @return Returns INT_MIN if the stack is empty and the top of the stack item otherwise
 */
cell_t peek(Stack *stack);

/**
 * Frees all memory allocated for the stack
 * @param stack The stack struct which shall be deleted
 */
void deleteStack(Stack *stack);

/**
 * Resets the top of the stack back to -1
 * @param stack The stack strcut which shall be cleared
 */
void clearStack(Stack *stack);

/**
 * Gives back the number of elements on the stack
 * @param stack
 * @return
 */
int numberOfElements(Stack *stack);

/**
 * Returns the element which is 'index' places from the top of the stack
 * or nil if there are not enough elements
 * @param stack
 * @param index
 * @return
 */
cell_t pickElement(Stack *stack, cell_t index);

/**
 * Drops the elemnt on the "index" place from the stack an returns it
 * @param stack
 * @param index
 * @return
 */
cell_t dropElement(Stack *stack, cell_t index);

#endif //AMFORTH_STACK_H
