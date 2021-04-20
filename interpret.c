#include <ctype.h>
#include "interpret.h"
#include "executor.h"

char last_char;

void interpret() {

    int len = nextToken(&token);
    //check if an error occurred or the the user wants to quit
    if (len == -1) {
        ERROR("Token parsing failed");
        free_res();
        exit(1);
    } else if (len == 0) {
        //reached EOF
        free_res();
        exit(0);
    } else if (len >= MAX_WORD_NAME_SIZE) {
        WORD_SIZE_LIMIT();
    } else if (strcmp(token, "bye") == 0) {
        fprintf(stdout, "see you later!\n");
        free_res();
        exit(EXIT_SUCCESS);
    } else {
        push(parameterStack, (cell_t) &token);
    }

}

void free_res() {
    if (token != NULL) free(token);
    deleteDict();
    defs = &macros;
    deleteDict();
    deleteStack(parameterStack);
    deleteStack(returnStack);
}

void skipLine() {
    if (last_char != '\n') {
        char c;
        while ((c = getc(stream)) != '\n');
    }
}

char getNextChar() {
    if (last_char == '\n') {
        PRINT_INPUT_OK();
    }

    return (last_char = fgetc(stream));
}

int nextToken(char **token_ptr) {

    //if token_ptr is NULL, then acquire memory
    if (*token_ptr == NULL) *token_ptr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*token_ptr == NULL) return -1;

    //get next char from stream
    char currentChar = getNextChar();

    int len = 0;
    while (!isspace(currentChar)) {

        if (currentChar == EOF) {
            return 0;  //immediately return if the EOF has been reached
        }

        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            (*token_ptr)[len] = currentChar;
        }

        len++;
        currentChar = getNextChar();    //read in next char for next loop iteration,
        // even if MAX_WORD_NAME_SIZE has been reached
    }

    //getting rid of whitespaces by recursively calling nextToken
    //until a string with len > 0 is found
    if (len == 0) {
        return nextToken(token_ptr);
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


/*int nextToken(char** token_ptr){
    return nextTokenFromLine(line, token_ptr, nread);
}*/

/*
int nextTokenFromLine(char *line, char **token_ptr, ssize_t nread) {
    static int line_index = 0; //pointer of the current character of the line

    //check if end of line has been reached
    if (line_index == nread) {
        line_index = 0;
        return 0;
    }

    //if token_ptr is NULL, then acquire memory
    if (*token_ptr == NULL) *token_ptr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*token_ptr == NULL) return -1;

    //get next char from stream and also increment the index (important for recursive calls)
    char currentChar = line[line_index];
    line_index++;

    int len = 0;
    while (!isspace(currentChar) && (line_index < nread)) {

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
*/
void PRINT_INPUT_OK() {
    if (stream == stdin) fprintf(stdout, "ok> ");
}

void WORD_SIZE_LIMIT() {
    ERROR("Token exceeds number of chars");
}