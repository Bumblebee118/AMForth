#include <ctype.h>
#include "interpret.h"
#include "executor.h"

char lastChar;

void interpret() {
    int len;
    char *string;
    if (isStringMode) {
        len = getStringFromInput(&string, &token);
    } else {
        len = nextToken(&token);
    }

    //check if an error occurred or the the user wants to quit
    if (len == -1) {
        ERROR("Token parsing failed");
        free_res();
        exit(1);
    } else if (len == 0) {
        //reached EOF
        free_res();
        exit(0);
    } else if (len >= MAX_WORD_NAME_SIZE && !isStringMode) {
        WORD_SIZE_LIMIT();
    } else if ((strcmp(token, "bye") == 0) && !isStringMode) {
        fprintf(stdout, "see you later!\n");
        free_res();
        exit(EXIT_SUCCESS);
    } else {
        if (isStringMode) {
            push(parameterStack, (cell_t) string);
            push(parameterStack, (cell_t) &token);
        } else {
            push(parameterStack, (cell_t) &token);
        }
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
    if (lastChar != '\n') {
        char c;
        while ((c = (char) getc(stream)) != '\n');
    }
}

char getNextChar() {
    if (lastChar == '\n') {
        PRINT_INPUT_OK();
    }

    return (lastChar = (char) fgetc(stream));
}

int nextToken(char **tokenPtr) {

    //if tokenPtr is NULL, then acquire memory
    if (*tokenPtr == NULL) *tokenPtr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    //check pointer again
    if (*tokenPtr == NULL) return -1;

    //get next char from stream
    char currentChar = getNextChar();

    int len = 0;
    while (!isspace(currentChar)) {

        if (currentChar == EOF) {
            return 0;  //immediately return if the EOF has been reached
        }

        //only add new chars to string, it MAX_WORD_NAME_SIZE has not been exceeded
        if (len < MAX_WORD_NAME_SIZE - 1) {
            (*tokenPtr)[len] = currentChar;
        }

        len++;
        currentChar = getNextChar();    //read in next char for next loop iteration,
        // even if MAX_WORD_NAME_SIZE has been reached
    }

    //getting rid of whitespaces by recursively calling nextToken
    //until a string with len > 0 is found
    if (len == 0) {
        return nextToken(tokenPtr);
    }

    //add zero delimiter at the end of string
    //special handling string with size bigger than MAX_WORD_NAME_SIZE
    if (len < MAX_WORD_NAME_SIZE - 1) {
        (*tokenPtr)[len] = '\0';
    } else {
        (*tokenPtr)[MAX_WORD_NAME_SIZE - 1] = '\0';
    }

    return len;
}

int getStringFromInput(char **pString, char **tokenPtr) {
    *tokenPtr = malloc(sizeof(char) * MAX_WORD_NAME_SIZE);
    if (*tokenPtr == NULL) return -1;
    *tokenPtr[0] = '"';
    *tokenPtr[1] = '\0';
    *tokenPtr[2] = '\0';
    *tokenPtr[3] = '\0';

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

        if (((*pString)[len] == ' ' || (*pString)[len] == '\n' )&& (*pString)[len - 1] == '"') {
            singleQuotationMark = 1;

        }

        len++;
        if (currentChar != '\n') {
            currentChar = getNextChar();
        } else {
           PRINT_INPUT_OK();
           // avoid two "ok"s
           lastChar = ' ';
        }
    }

    (*pString)[len-2] = '\0';
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