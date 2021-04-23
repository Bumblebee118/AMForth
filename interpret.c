#include <ctype.h>
#include "interpret.h"
#include "executor.h"

char lastChar;

void interpret() {
    int len;
    char *string = NULL;
    if (isStringMode) {
        len = getStringFromInput(&string, &token);
    } else {
        len = nextToken();
    }

    //check if an error occurred or the the user wants to quit
    if (len == -1) {
        push(parameterStack, ERR_PARSING_ERROR);
        THROW();
        freeRes(string);
        exit(1);
    } else if (len == 0) {
        //reached EOF
        freeRes(string);
        exit(0);
    } else if (len >= MAX_WORD_NAME_SIZE && !isStringMode) {
        push(parameterStack, ERR_TOKEN_SIZE_LIMIT);
        THROW();
    } else if ((strcmp(token, "bye") == 0) && !isStringMode) {
        fprintf(stdout, "see you later!\n");
        freeRes(string);
        exit(EXIT_SUCCESS);
    } else {
        if (isStringMode) {
            push(parameterStack, (cell_t) string);
            push(parameterStack, (cell_t) token);
        } else {
            push(parameterStack, (cell_t) token);
        }
    }

}

void freeRes(char *string) {
    if (token != NULL) free(token);
    if (string != NULL) free(string);
    deleteDict();
    defs = &macros;
    deleteDict();
    deleteStack(parameterStack);
    deleteStack(returnStack);
}

void skipLine() {
    if (lastChar != '\n') {
        char c;
        while ((c = (char) getc(stream)) != '\n');
    }
}

char getNextChar() {
    if (lastChar == '\n') {
        if (isCompileMode == 0) print_msg("ok> ");
        else print_msg("compiled> ");
    }

    return (lastChar = (char) fgetc(stream));
}

int nextToken() {
    if(token == NULL){
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

int getStringFromInput(char **pString, char **tokenPtr) {
    *tokenPtr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    if (*tokenPtr == NULL) return -1;
    *tokenPtr[0] = '"';
    // *tokenPtr[1] = '\0';

    int bufferSize = BASE_STRING_SIZE;
    *pString = (char *) malloc(sizeof(char) * bufferSize);
    if (*pString == NULL) return -1;

    char currentChar = getNextChar();

    int len = 0;
    int singleQuotationMark = 0;
    while (!singleQuotationMark) {
        if (currentChar == EOF) return 0;

        if (len + 1 < bufferSize) {
            (*pString)[len] = currentChar;
        } else {
            bufferSize += 2;
            *pString = realloc(pString, bufferSize);
            (*pString)[len] = currentChar;
        }

        currentChar = getNextChar();
        if ((currentChar == ' ' || currentChar == '\n') && (*pString)[len] == '"') singleQuotationMark = 1;
        len++;
    }

    (*pString)[len - 1] = '\0';
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
void print_msg(char* msg) {
    if (stream == stdin) fprintf(stdout, "%s", msg);
}
