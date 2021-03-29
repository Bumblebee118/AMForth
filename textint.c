#include "textint.h"
#include <stdio.h>
#include <malloc.h>
#include <mem.h>

void startTextInterpreter(FILE* stream){

    int quit = 0;
    char* token = NULL;

    while (quit == 0){

        int len = nextToken(stream, &token);    //get next token from stream

        if(len == -1){          //malloc failed
            printf("malloc has failed\n");
            quit = 1;
        }else if(len == -2) {   //token is to big
            printf("size of token exceeds MAX_WORD_NAME_SIZE\n");
            quit = 1;
        }else if(strcmp(token, "bye") == 0){
                printf("see you later!\n");
                quit = 1;
        }else if(len != 0){
            printf("token is: %s - len: %d\n", token, len);

        }
    }

    //free token if quit
    if(token != NULL){
        free(token);
    }
}

int nextToken(FILE* stream, char** token){
    //if token is not NULL, then free the space
    if(*token != NULL){
        free(*token);
    }

    //acquire new memory space for the token
    int size = MIN_WORD_NAME_SIZE;
    *token = malloc(sizeof(char)*size);

    if (*token == NULL){
        return -1;
    }

    int len = 0;
    //get next char from stream
    char currentChar = fgetc(stream);
    if(currentChar == EOF){
        return -1;
    }

    while((currentChar != ' ') && (currentChar != '\t') && (currentChar != '\n') && (currentChar != EOF)){
        //if the lenght of the token exceeds the current size, reallocate
        if(len == size-1){
            size *= 2;
            //check boundaries
            if(size < MAX_WORD_NAME_SIZE){
                *token = (char*) realloc(*token, sizeof(char)*size);
            }else{
                return -2;
            }
        }

        (*token)[len] = currentChar;
        len++;
        currentChar = fgetc(stream);
    }

    //add zero delimiter at the end of string
    (*token)[len] = '\0';

    return len;
}