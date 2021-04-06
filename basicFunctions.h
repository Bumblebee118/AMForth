//
// Created by Stefan Walser on 30.03.21.
//

#ifndef AMFORTH_BASICFUNCTIONS_H
#define AMFORTH_BASICFUNCTIONS_H

#include "stack.h"

/**
 * adds the top most two numbers on the stack and pushes the result back onto the stack
 * @param stack the stack
 */
int ADD(Stack *stack);

/**
 * subtracts the top most two numbers on the stack and pushes the result back onto the stack
 * @param stack the stack
 */
int SUBTRACT(Stack *stack);

/**
 * multiplies the top most two numbers on the stack and pushes the result back onto the stack
 * @param stack the stack
 */
int MULTIPLY(Stack *stack);

/**
 * divides the top most two numbers on the stack and pushes the result back onto the stack
 * @param stack the stack
 */
int DIVIDE(Stack *stack);

/**
 * Pops the top element of the stack in prints it to stdout
 * @param stack
 */
int PRINTPOPSTACK(Stack *stack);

/**
 * Prints content of the whole stack without modifying the stack
 * @param stack
 */
int PRINTSTACK(Stack *stack);

typedef int (*BASICFUNC)(Stack *);

typedef int (*FUNCDEF)(Stack *, int*);

#endif //AMFORTH_BASICFUNCTIONS_H
