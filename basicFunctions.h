//
// Created by Stefan Walser on 30.03.21.
//

#ifndef AMFORTH_BASICFUNCTIONS_H
#define AMFORTH_BASICFUNCTIONS_H

#include "stack.h"

/**
 * adds the top most two numbers on the stack
 */
void ADD(Stack *stack);

void SUBTRACT(Stack *stack);

typedef void (*BASICFUNC)(Stack *);

#endif //AMFORTH_BASICFUNCTIONS_H
