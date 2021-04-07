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

/**
 * global variable for a the current token being processed
 */
char *token;

static int error_cnt = 0;

Dict *dict;
Stack *parameterStack;

#endif //AMFORTH_GLOBAL_H
