#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpret.h"

void startInterpret(FILE *stream, Dict *dict, Stack *parameterStack) {

    int quit = 0;
    char *token = NULL;

    printf("Type 'bye' to exit\n");

    while (quit == 0) {

        int len = nextToken(stream, &token);    //get next token from stream

        if (len == -1) {          //malloc failed
            printf("error occured during parsing\n");
            quit = 1;
        } else if (len >= MAX_WORD_NAME_SIZE) {   //token is to big
            printf("size of token exceeds MAX_WORD_NAME_SIZE\n");
            //quit = 1;
        } else if (strcmp(token, "bye") == 0) {
            printf("see you later!\n");
            quit = 1;
        } else if (len != 0) {
            // printf("token is: %s - len: %d\n", token, len);

            DictEntry *entry = getEntry(dict, token);
            if(entry == NULL){

               char* endptr;
               int num = strtol(token, &endptr, 10);

               if (strlen(endptr)==0){
                   push(parameterStack, num);
                   PRINT_INPUT_OK(stream);
               }
               else{
                   ERROR_WORD_NOT_FOUND(token);
                   clearStack(parameterStack);
               }

            }else{
                //TODO Execute function definition here
                entry->basicfunc(parameterStack);
                PRINT_INPUT_OK(stream);
            }

        }
    }

    //free token if quit
    if (token != NULL) {
        free(token);
    }
}


int nextToken(FILE *stream, char **token_ptr) {
    //if token_ptr is NULL, then acquire memory
    if (*token_ptr == NULL) *token_ptr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*token_ptr == NULL) return -1;

    //get next char from stream
    char currentChar = fgetc(stream);
    if (currentChar == EOF) {
        return -1;  //immediately return if the EOF has been reached
    }

    int len = 0;
    while ((currentChar != ' ') && (currentChar != '\t') && (currentChar != '\n') && (currentChar != '\r') &&
           (currentChar != EOF)) {
        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            (*token_ptr)[len] = currentChar;
        }

        len++;
        currentChar = fgetc(
                stream); //read in next char for next loop iteration, even if MAX_WORD_NAME_SIZE has been reached
    }

    //getting rid of whitespaces by recursively calling nextToken
    //until a string with len > 0 is found
    if (len == 0) {
        return nextToken(stream, token_ptr);
    }

    //add zero delimiter at the end of string
    //special handling string with size bigger than MAX_WORD_NAME_SIZE
    if (len < MAX_WORD_NAME_SIZE - 1) {
        (*token_ptr)[len] = '\0';
    } else {
        (*token_ptr)[MAX_WORD_NAME_SIZE - 1] = '\0';
    }

    return len;
}

void ERROR_WORD_NOT_FOUND(char* word){
    printf("Undefined word '%s'\n", word);
}

void PRINT_INPUT_OK(FILE* stream){
    if (stream == stdin) printf(" ok\n");
}