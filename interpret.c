#include <ctype.h>
#include "interpret.h"
#include "executor.h"

char lastChar= 0;
int redefined = 0;

void interpret() {
    int len;
    len = nextToken();

    //check if an error occurred or the the user wants to quit
    if (len == -1) {
        push(parameterStack, ERR_PARSING_ERROR);
        THROW();
        freeRes();
        exit(1);
    } else if (len == 0) {
        //reached EOF
        if(stream == stdin){
            freeRes();
            exit(EXIT_SUCCESS);
        }
        fclose(stream);
        ip = start; //reset ip
        stream = stdin;
    } else if (len >= MAX_WORD_NAME_SIZE) {
        push(parameterStack, ERR_TOKEN_SIZE_LIMIT);
        THROW();
    } else if ((strcmp(token, "bye") == 0)) {
        print_msg("see you later!\n");
        freeRes();
        exit(EXIT_SUCCESS);
    } else {

        //if the word exists in the dictionary, execute the definition
        if ((wp = getEntry(token))) {
            push(parameterStack, (cell_t) wp);
            if (isCompileMode) COMPILE();
            else EXECUTE();
            return;
        }

        //check if it is a macro
        defs = &macros;
        if ((wp = getEntry(token))) {
            if (isCompileMode) COMPILE();
            else {
                defs = &dict;
                push(parameterStack, ERR_INTERPRET_COMPILE_ONLY);
                THROW();
            }
            return;
        }
        defs = &dict;

        //check if it is a number
        char *endptr;
        cell_t num = (cell_t) strtol(token, &endptr, 10);

        if (strlen(endptr) == 0) {
            push(parameterStack, num);
            if (isCompileMode) {
                push(parameterStack, (cell_t) dolit_wp);
                COMPILE();
            }
        } else {
            push(parameterStack, ERR_UNDEFINED_WORD);
            THROW();
        }
    }
}

void freeRes() {
    if (token != NULL) free(token);
    deleteDict();
    defs = &macros;
    deleteDict();
    deleteStack(parameterStack);
    deleteStack(returnStack);
    deleteList(ptrList);
}

void skipLine() {
    if (lastChar != '\n') {
        while ((char) getc(stream) != '\n');
    }
}

char getNextChar() {
    //print input when reading from file
    if(stream!=stdin && lastChar>0) fprintf(stdout, "%c", lastChar);

    if (lastChar == '\n') {
        if (isCompileMode == 0) print_msg(" ok> ");
        else print_msg(" compiled> ");
    }
    return (lastChar = (char) fgetc(stream));
}

int nextToken() {
    if (token == NULL) {
        //acquire memory
        token = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
        //check pointer again
        if (token == NULL) return -1;
    }

    //get next char from stream
    char currentChar = getNextChar();

    int len = 0;
    while (!isspace(currentChar)) {
        if (currentChar == EOF) {
            return 0;  //immediately return if the EOF has been reached
        }

        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            token[len] = currentChar;
        }

        len++;
        currentChar = getNextChar();    //read in next char for next loop iteration,
        // even if MAX_WORD_NAME_SIZE has been reached
    }

    //getting rid of whitespaces by recursively calling nextToken
    //until a string with len > 0 is found
    if (len == 0) {
        return nextToken();
    }

    //add zero delimiter at the end of string
    //special handling string with size bigger than MAX_WORD_NAME_SIZE
    if (len < MAX_WORD_NAME_SIZE - 1) {
        token[len] = '\0';
    } else {
        token[MAX_WORD_NAME_SIZE - 1] = '\0';
    }

    return len;
}


cell_t nextString(char** str){
    cell_t len = 0;
    int size = BASE_STRING_SIZE;
    char current = getNextChar();
    while((current != '\"') && (current != '\n')){
        if(len == size-1){
            size += 2;
            (*str) = (char *) realloc(str, sizeof(char)*size);
        }
        (*str)[len] = current;
        len++;
        current = getNextChar();
    }
    (*str)[len] = '\0';


    //store pointer in list
    ptrList = add(ptrList, *str);
    if(ptrList==NULL){
        push(parameterStack, ERR_NO_MEMORY);
        THROW();
        exit(EXIT_FAILURE);
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
void print_msg(char *msg) {
    fprintf(stdout, "%s", msg);
    fflush(stdout);
}
