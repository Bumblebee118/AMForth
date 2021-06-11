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
#include "list.h"

#define MAX_WORD_NAME_SIZE 128          //maximum number of chars one word can have
#define STANDARD_STACK_CAPACITY 128
#define CODE_SIZE 32768
#define HEAP_SIZE 32768*100
#define BASE_STRING_SIZE 128

#define FALSE 0
#define TRUE !FALSE

/**
 *
 */
extern char *token;

extern int loopDepth;

/**
 * one global dictionary for the whole program
 */
extern Dict *dict;
extern Dict *dict_begin; //begin of dictionary

/**
 * user definitions segment for compiling
 */
extern Dict *user_code_base[CODE_SIZE];

/**
 * heap for variables
 */
extern cell_t variable_space[HEAP_SIZE];
extern cell_t* heapptr;
extern cell_t* heap;


/**
 * save base address
 */
extern Dict **userCode;
extern Dict **start; //start of user code

/**
 * one global macros for the whole program
 */
extern Dict *macros;
extern Dict* macros_begin; //begin of macro definition

/**
 * one global parameter stack for the whole program
 */
extern Stack *parameterStack;

/**
 * one global return stack for the whole program
 */
extern Stack *returnStack;

/**
 * list that keeps track of all user allocated memory
 */
extern List* ptrList;

/**
 * specifies the mode the interpreter is currently in
 */
extern cell_t* isCompileMode;

/**
 * Input stream of the program definitions
 */
extern FILE *stream;

/**
 * direct threaded definitions pointers
 */
extern Dict *wp;    //current word pointer
extern Dict **ip;   //current instr pointer
extern Dict *cw;   //current compiled word

extern Dict **defs; //can either point to dict or macro address

extern long nil;

extern int redefined;

/**
 * dictionary pointer to important words
 * used for compiling
 */
extern Dict* dolit_wp;
extern Dict* checkbranch_wp;
extern Dict* branch_wp;
extern Dict* assignvar_wp;
extern Dict* pushonreturn_wp;
extern Dict* popfromreturn_wp;
extern Dict* peekfromreturn_wp;
extern Dict* fetchvar_wp;
extern Dict* gt_wp;
extern Dict* add_wp;
extern Dict* dosemi_wp;
extern Dict* dostorestring_wp;
extern Dict* doprintstring_wp;

/**
 * variable pointer
 */
extern Dict* i_wp;
extern Dict* k_wp;
extern Dict* j_wp;

#endif //AMFORTH_GLOBAL_H
