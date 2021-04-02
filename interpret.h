//
// Created by Alexander on 29.03.2021.
//

#ifndef AMFORTH_INTERPRET_H
#define AMFORTH_INTERPRET_H

#define MAX_WORD_NAME_SIZE 128          //maximum number of chars one word can have

#include <stdio.h>
#include "dict.h"

/**
 * Starts the text interpreter, which reads in tokens from the input stream 'stream'
 * tokens can be separated by an arbitrary amount of whitespaces or tabs
 * @param stream Can be a file or stdin
 */
void startInterpret(FILE *stream, Dict *dict, Stack *parameterStack);

/**
 * Reads in the next token_ptr from the input stream 'stream'
 * @param stream Can be a file or stdin
 * @param token_ptr an char** pointer, which will be filled with the next token_ptr
 * @return Returns the length of the read token_ptr, -1 if an error occurs
 * token_ptr exceeds MAX_WORD_NAME_SIZE
 */
int nextToken(FILE *stream, char **token_ptr);

/**
 *
 * @param word
 */
void ERROR_WORD_NOT_FOUND(char* word);

/**
 *
 * @param stream
 */
void PRINT_INPUT_OK(FILE* stream);

#endif //AMFORTH_INTERPRET_H
