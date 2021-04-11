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
static int error_cnt = 0;

/**
 * one global dictionary for the whole program
 */
Dict *dict;

/**
 * one global parameter stack for the whole program
 */
Stack *parameterStack;

#endif //AMFORTH_GLOBAL_H
