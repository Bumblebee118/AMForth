//
// Created by Alexander on 29.03.2021.
//

#ifndef AMFORTH_INTERPRET_H
#define AMFORTH_INTERPRET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dict.h"

/**
 * Starts the text interpreter, which reads in tokens from the input stream 'stream'
 * tokens can be separated by an arbitrary amount of whitespaces or tabs
 * @param stream Can be a file or stdin
 */
void startInterpret(FILE *stream);

/**
 * Reads in the next token_ptr from the input stream 'stream'
 * @param stream Can be a file or stdin
 * @param token_ptr an char** pointer, which will be filled with the next token_ptr
 * @return Returns the length of the read token_ptr, -1 if an error occurs
 * token_ptr exceeds MAX_WORD_NAME_SIZE
 */
int nextToken(FILE *stream, char **token_ptr);

/**
 * Reads in the next token from the string 'line'
 * @param line The string from which a new token shall be read
 * @param token_ptr Address of a char array which will be filled with a new token
 * @return Returns the length of the token, -1 if an error occurs
 * or 0 if there are new more tokens left in that line
 */
int nextTokenFromLine(char* line, char **token_ptr, ssize_t nread);

/**
 * Print 'ok' to stdin if the interpreter is run in interactive mode
 * @param stream
 */
void PRINT_INPUT_OK(FILE* stream);

#endif //AMFORTH_INTERPRET_H
