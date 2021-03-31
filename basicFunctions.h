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
void ADD(Stack *stack);

/**
 * subtracts the top most two numbers on the stack and pushes the result back onto the stack
 * @param stack the stack
 */
void SUBTRACT(Stack *stack);

/**
 * multiplies the top most two numbers on the stack and pushes the result back onto the stack
 * @param stack the stack
 */
void MULTIPLY(Stack *stack);

/**
 * divides the top most two numbers on the stack and pushes the result back onto the stack
 * @param stack the stack
 */
void DIVIDE(Stack *stack);

typedef void (*BASICFUNC)(Stack *);

#endif //AMFORTH_BASICFUNCTIONS_H
