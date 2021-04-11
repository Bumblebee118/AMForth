//
// Created by Stefan Walser on 30.03.21.
//

#ifndef AMFORTH_BASICFUNCTIONS_H
#define AMFORTH_BASICFUNCTIONS_H

#include <limits.h>

/**
 * typedefs for function pointers
 */
typedef int (*BASICFUNC)();
typedef int (*CODEPOINTER)(Stack *, int *);

/**
 * adds the top most two numbers on the stack and pushes the result back onto the stack
 */
int ADD();

/**
 * subtracts the top most two numbers on the stack and pushes the result back onto the stack
 */
int SUBTRACT();

/**
 * multiplies the top most two numbers on the stack and pushes the result back onto the stack
 */
int MULTIPLY();

/**
 * divides the top most two numbers on the stack and pushes the result back onto the stack
 */
int DIVIDE();

/**
 * Pops the top element of the stack in prints it to stdout
 */
int PRINTPOPSTACK();

/**
 * Prints content of the whole stack without modifying the stack
 */
int PRINTSTACK();

/**
 * starts compile mode
 * @return
 */
int DOCOLON();


#endif //AMFORTH_BASICFUNCTIONS_H
