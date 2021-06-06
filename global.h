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
Dict *dict_begin; //begin of dictionary

/**
 * user definitions segment for compiling
 */
Dict *userCodeBase[CODE_SIZE];

/**
 * save base address
 */
extern Dict **userCode;
extern Dict **start; //start of user code

/**
 * one global macros for the whole program
 */
Dict *macros;
Dict* macros_begin; //begin of macro definition

/**
 * one global parameter stack for the whole program
 */
Stack *parameterStack;

/**
 * one global return stack for the whole program
 */
Stack *returnStack;

/**
 * list that keeps track of all user allocated memory
 */
List* ptrList;

/**
 * specifies the mode the interpreter is currently in
 */
extern int isCompileMode;

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

extern int redefined;

/**
 * dictionary pointer to important words
 */
Dict* dolit_wp; //pointer to dolit
Dict* checkbranch_wp;
Dict* branch_wp;
Dict* assignvar_wp;
Dict* por_wp;
Dict* pfr_wp;
Dict* fetchvar_wp;
Dict* gt_wp;
Dict* add_wp;
Dict* dosemi_wp;
Dict* dostorestring_wp;
Dict* doprintstring_wp;

/**
 * variable pointer
 */
Dict* i_wp;
Dict* k_wp;
Dict* j_wp;

#endif //AMFORTH_GLOBAL_H
