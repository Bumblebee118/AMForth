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
void interpret();

/**
 * frees all allocated memory of token, dict and the stacks
 */
void freeRes(char *token, char *string);

/**
 * skips all chars until the next '\n' in input stream
 */
void skipLine();

/**
 * gets the next char from the input stream and saves the this char in a variable
 * @return next char from stream
 */
char getNextChar();

/**
 * Reads in the next tokenPtr from the input stream 'stream'
 * @param stream Can be a file or stdin
 * @param tokenPtr an char** pointer, which will be filled with the next tokenPtr
 * @return Returns the length of the read tokenPtr, -1 if an error occurs
 * tokenPtr exceeds MAX_WORD_NAME_SIZE
**/
int nextToken(char **tokenPtr);

/**
 * Reads in the next token_ptr from the current line
 * @param token_ptr an char** pointer, which will be filled with the next token_ptr
 * @return Returns the length of the read token_ptr, -1 if an error occurs
 * token_ptr exceeds MAX_WORD_NAME_SIZE
 */
//int nextToken(char** token_ptr);

/**
 * Reads in the next token from the string 'line'
 * @param line The string from which a new token shall be read
 * @param token_ptr Address of a char array which will be filled with a new token
 * @return Returns the length of the token, -1 if an error occurs
 * or 0 if there are new more tokens left in that line
 */
int nextTokenFromLine(char* line, char **token_ptr, ssize_t nread);

/**
 *
 * @param pString an char** pointer, which will be filled with the next pString
 * @return Returns the length of the token, -1 if an error occurs
 */
int getStringFromInput(char **pString, char **tokenPtr);

/**
 * Print 'ok' to stdin if the interpreter is run in interactive mode
 * @param stream
 */
void PRINT_INPUT_OK();

void WORD_SIZE_LIMIT(char *token);

#endif //AMFORTH_INTERPRET_H
