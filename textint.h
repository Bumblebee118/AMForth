//
// Created by Alexander on 29.03.2021.
//

#ifndef AMFORTH_TEXTINT_H
#define AMFORTH_TEXTINT_H

#define MIN_WORD_NAME_SIZE 8    //minimum number of chars for token string
#define MAX_WORD_NAME_SIZE 128  //maximum number of chars one word can have

#include <stdio.h>

/**
 * Starts the text interpreter, which reads in tokens from the input stream 'stream'
 * tokens can be separated by an arbitrary amount of whitespaces or tabs
 * @param stream Can be a file or stdin
 */
void startTextInterpreter(FILE* stream);

/**
 * Reads in the next token from the input stream 'stream'
 * @param stream Can be a file or stdin
 * @param token an char** pointer, which will be filled with the next token
 * @return Returns the length of the read token, -1 if malloc fails, -2 if the size of the
 * token exceeds MAX_WORD_NAME_SIZE
 */
int nextToken(FILE* stream, char** token);

#endif //AMFORTH_TEXTINT_H
