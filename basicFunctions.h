//
// Created by Stefan Walser on 30.03.21.
//

#ifndef AMFORTH_BASICFUNCTIONS_H
#define AMFORTH_BASICFUNCTIONS_H

#include <limits.h>

/**
 * typedefs for function pointers
 */
typedef void (*BASICFUNC)();
typedef int (*CODEPOINTER)(Stack *, int *);

/**
 * adds the top most two numbers on the stack and pushes the result back onto the stack
 */
void ADD();

/**
 * subtracts the top most two numbers on the stack and pushes the result back onto the stack
 */
void SUBTRACT();

/**
 * multiplies the top most two numbers on the stack and pushes the result back onto the stack
 */
void MULTIPLY();

/**
 * divides the top most two numbers on the stack and pushes the result back onto the stack
 */
void DIVIDE();

/**
 * Pops the top element of the stack in prints it to stdout
 */
void PRINTPOPSTACK();

/**
 * Prints content of the whole stack without modifying the stack
 */
void PRINTSTACK();

/**
 * starts compile mode
 * @return
 */
void DOCOLON();

/**
 *
 */
void COLON();


void DOSEMI();
void SEMI();

void INTERPRET();
void EXECUTE();
void BRANCH0();
#endif //AMFORTH_BASICFUNCTIONS_H
