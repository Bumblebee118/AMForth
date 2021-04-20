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
#define MAX_DEFINITION_SIZE  32768

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
dict_t *dict;

/**
 * user definitions segment for compiling
 */
dict_t* user_code_base[MAX_DEFINITION_SIZE];

/**
 * save base address
 */
extern dict_t** user_code;
extern dict_t** start;

/**
 * one global macros for the whole program
 */
dict_t *macros;

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
 * Input stream of the program definitions
 */
FILE* stream;

/**
 * direct threaded definitions pointers
 */
extern dict_t *wp;    //current word pointer
extern dict_t **ip;   //current instr pointer
extern dict_t *cw;   //current compiled word

extern dict_t** defs; //can either point to dict or macro address

#endif //AMFORTH_GLOBAL_H
