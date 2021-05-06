//
// Created by Stefan Walser on 07.04.21.
//

#ifndef AMFORTH_GLOBAL_H
#define AMFORTH_GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include "interpret.h"
#include "executor.h"
#include "compiler.h"
#include "dict.h"
#include "stack.h"
#include "error.h"

#define MAX_WORD_NAME_SIZE 128          //maximum number of chars one word can have
#define STANDARD_STACK_CAPACITY 128
#define CODE_SIZE  32768
#define BASE_STRING_SIZE 128

#define FALSE 0
#define TRUE !FALSE

/**
 *
 */
extern char *token;

int loopDepth;

/**
 * one global dictionary for the whole program
 */
Dict *dict;

/**
 * user definitions segment for compiling
 */
Dict *userCodeBase[CODE_SIZE];

/**
 * save base address
 */
extern Dict **userCode;
extern Dict **start;

/**
 * one global macros for the whole program
 */
Dict *macros;

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
extern int isCompileMode;

/**
 * specifies if the interpreter is reading a string from the stream
 */
extern int isStringMode;

/**
 * Input stream of the program definitions
 */
FILE *stream;

/**
 * direct threaded definitions pointers
 */
extern Dict *wp;    //current word pointer
extern Dict **ip;   //current instr pointer
extern Dict *cw;   //current compiled word

extern Dict **defs; //can either point to dict or macro address

extern long nil;

#endif //AMFORTH_GLOBAL_H
