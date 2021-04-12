//
// Created by Stefan Walser on 07.04.21.
//

#ifndef AMFORTH_GLOBAL_H
#define AMFORTH_GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "stack.h"
#include "error.h"

#define MAX_WORD_NAME_SIZE 128          //maximum number of chars one word can have
#define STANDARD_STACK_CAPACITY 128

/**
 * global variable for a the current token being processed
 */
char *token;

/**
 * global variable for error counts
 */
extern int error_cnt;

/**
 * one global dictionary for the whole program
 */
Dict *dict;

/**
 * one global parameter stack for the whole program
 */
Stack *parameterStack;

/**
 * one global return stack for the whole program
 */
Stack *returnStack;

/**
 * specifies the mode the interpreter is currently in
 */
extern int inCompileMode;

/**
 * direct threaded code pointers
 */
extern DictEntry *wordPointer;
extern DictEntry *instrPointer;
extern DictEntry *progPointer;

#endif //AMFORTH_GLOBAL_H
