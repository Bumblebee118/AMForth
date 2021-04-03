#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpret.h"

void startInterpret(FILE *stream, Dict *dict, Stack *parameterStack) {

    int quit = 0;
    char *token = NULL;

    printf("Type 'bye' to exit\n");

    /*while (quit == 0) {

        int len = nextToken(stream, &token);    //get next token from stream
       // printf("token is: %s - len: %d\n", token, len);

        if (len == -1) {          //malloc failed
            printf("error occured during parsing\n");
            quit = 1;
        } else if (len >= MAX_WORD_NAME_SIZE) {   //token is to big
                printf("size of token exceeds MAX_WORD_NAME_SIZE\n");
                //quit = 1;
        }
        else if (strcmp(token, "bye") == 0) {
            printf("see you later!\n");
            quit = 1;
        }
        else if (len != 0) {
            //printf("token is: %s - len: %d\n", token, len);

            DictEntry *entry = getEntry(dict, token);
            if(entry == NULL){
                char* endptr;
                int num = strtol(token, &endptr, 10);

                if (strlen(endptr)==0){
                        push(parameterStack, num);
                }
                else{
                    ERROR_WORD_NOT_FOUND(token);
                    clearStack(parameterStack);
                }

            }else{
                //TODO Execute function definition here
                entry->basicfunc(parameterStack);
            }

            if (len == -2){
                PRINT_INPUT_OK(stream);
            }

        }


    }*/

    char* line = NULL;
    size_t  length = 0;
    ssize_t nread;

    if ((nread = getline(&line, &length, stream)) == -1){
        quit = 1;
    }else{
        fwrite(line, nread-1, 1, stdout);
    }

    while (quit == 0) {

        int len = nextTokenFromLine(line, &token, nread);    //get next token from stream
        //printf("token is: %s - len: %d\n", token, len);

        if(len == -2){
            PRINT_INPUT_OK(stream);

            //get new line if end has been reached
            if ((nread = getline(&line, &length, stream)) == -1){
                quit = 1;
            }else{
                fwrite(line, nread-1, 1, stdout);
            }

        }else{
            if (len == -1) {          //malloc failed
                printf("error occured during parsing\n");
                quit = 1;
            } else if (len >= MAX_WORD_NAME_SIZE) {   //token is to big
                printf("size of token exceeds MAX_WORD_NAME_SIZE\n");
                //quit = 1;
            }
            else if (strcmp(token, "bye") == 0) {
                printf("\nsee you later!\n");
                quit = 1;
            }
            else if (len != 0) {
                //printf("token is: %s - len: %d\n", token, len);

                DictEntry *entry = getEntry(dict, token);
                if(entry == NULL){
                    char* endptr;
                    int num = strtol(token, &endptr, 10);

                    if (strlen(endptr)==0){
                        push(parameterStack, num);
                    }
                    else{
                        ERROR_WORD_NOT_FOUND(token);
                        clearStack(parameterStack);
                    }

                }else{
                    //TODO Execute function definition here
                    entry->basicfunc(parameterStack);
                }
            }
        }
    }

    //free token if quit
    if (token != NULL) free(token);
    if (line != NULL) free(line);
}


int nextToken(FILE *stream, char **token_ptr) {
    //if token_ptr is NULL, then acquire memory
    if (*token_ptr == NULL) *token_ptr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*token_ptr == NULL) return -1;

    //get next char from stream
    char currentChar = fgetc(stream);

    int len = 0;
    while ((currentChar != ' ') && (currentChar != '\t') && (currentChar != '\r') ){
        if (currentChar == EOF) {
            return -1;  //immediately return if the EOF has been reached
        }

        if(currentChar == '\n'){
            return -2;  //return -2 is the current line has ended
        }

        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            (*token_ptr)[len] = currentChar;
        }

        len++;
        currentChar = fgetc(stream);    //read in next char for next loop iteration,
                                        // even if MAX_WORD_NAME_SIZE has been reached
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

int nextTokenFromLine(char* line, char **token_ptr, ssize_t nread) {
    static int line_index = 0;

    if(line_index == nread){
        line_index = 0;
        return -2;
    }

    //if token_ptr is NULL, then acquire memory
    if (*token_ptr == NULL) *token_ptr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*token_ptr == NULL) return -1;

    //get next char from stream
    char currentChar = line[line_index];
    line_index++;

    int len = 0;
    while ((currentChar != ' ') && (currentChar != '\t') && (currentChar != '\r') && (currentChar != '\n') && (line_index < nread)){

        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            (*token_ptr)[len] = currentChar;
        }

        len++;
        currentChar = line[line_index];     //read in next char for next loop iteration,
                                            // even if MAX_WORD_NAME_SIZE has been reached
        line_index++;
    }

    //getting rid of whitespaces by recursively calling nextToken
    //until a string with len > 0 is found
    if (len == 0) {
        return nextTokenFromLine(line, token_ptr, nread);
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