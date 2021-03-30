#include "textint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void startTextInterpreter(FILE *stream) {

    int quit = 0;
    char *token = NULL;

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
            printf("token is: %s - len: %d\n", token, len);

        }
    }

    //free token if quit
    if (token != NULL) {
        free(token);
    }
}

/*int nextToken(FILE* stream, char** token_ptr){
    if(*token_ptr == NULL) *token_ptr = malloc(sizeof(char)*MAX_WORD_NAME_SIZE);

    if(*token_ptr == NULL) return -1;
    int c;

    if((c = fscanf(stream, "%"MAX_WORD_NAME_SIZE_STR"s", *token_ptr)) != 1){
        printf("error at scanf, output %d\n", c);
        return -1;
    }

    int len = strlen(*token_ptr);
    if(len == MAX_WORD_NAME_SIZE-1){
        char nextChar = fgetc(stream);
        if ((nextChar != ' ') && (nextChar != '\t') && (nextChar != '\n')){
            printf("Word is too big\n");
            return -1;
        }
    }

    return len;

}*/

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