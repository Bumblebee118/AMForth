//
// Created by Stefan Walser on 30.03.21.
//

#include "global.h"

//init extern variable
int isCompileMode = 0;
int isStringMode = 0;

void ADD() {
    cell_t a = pop(parameterStack);
    if (a == nil) return;

    cell_t b = pop(parameterStack);
    if (b == nil) return;

    cell_t sum = a + b;
    push(parameterStack, sum);
}

void SUBTRACT() {
    cell_t b = pop(parameterStack);
    if (b == nil) return;

    cell_t a = pop(parameterStack);
    if (a == nil) return;

    cell_t diff = a - b;
    push(parameterStack, diff);
}

void MULTIPLY() {
    cell_t a = pop(parameterStack);
    if (a == nil) return;

    cell_t b = pop(parameterStack);
    if (b == nil) return;

    cell_t sum = a * b;
    push(parameterStack, sum);
}

void DIVIDE() {
    cell_t b = pop(parameterStack);
    if (b == nil) return;

    cell_t a = pop(parameterStack);
    if (a == nil) return;

    cell_t diff = a / b;
    push(parameterStack, diff);
}

void PRINTPOPSTACK() {
    cell_t a = pop(parameterStack);
    if (a == nil) return;

    fprintf(stdout, "%ld ", a);
}

void PRINTSTACK() {

    fprintf(stdout, "<%d> ", (parameterStack->top) + 1);

    int i = 0;
    while (i <= parameterStack->top) {
        fprintf(stdout, "%ld ", parameterStack->array[i]);
        i++;
    }
}

void DOCOLON() {
    //TODO repair
    push(returnStack, (cell_t) ip);
    ip = wp->definitions;
}

void COLON() {
    char *token;
    int len = nextToken(&token);

    if (len >= MAX_WORD_NAME_SIZE) {
        WORD_SIZE_LIMIT(token);
        return;
    }

    //compile("docol");
    cw = addEntry(token, 0, user_code, &DOCOLON);

    isCompileMode = 1;
}

void DOSEMI() {
    ip = (Dict **) pop(returnStack);
}

void SEMI() {
    compile("dosemi");
    isCompileMode = 0;
}

void DOLIT() {
    cell_t lit = (cell_t) *ip;
    push(parameterStack, lit);
    ip++;
}

void DOSTORESTRING() {
    cell_t string = (cell_t) *ip;
    push(parameterStack, string);
    ip++;
}

void DOPRINTSTRING() {
    char *string = (char *) (cell_t) *ip;
    fprintf(stdout, "%s ", string);
    ip++;
}

void NEXT() {
}

void INTERPRET() {
    interpret();
}

void EXECUTE() {
    char *word = (char *) pop(parameterStack);
    execute(word);
}

void BRANCH0() {
    //cell_t val = pop(parameterStack);
    //if(val == 0){
    ip = ip - 3;
    //}
}

void LISTWORDS() {
    Dict *pointer = dict;
    while (pointer != NULL) {
        fprintf(stdout, "%s ", (*pointer).word);
        pointer = (*pointer).link;
    }
}

void STARTSTORESTRING() {
    isStringMode = 1;
}

void STARTPRINTSTRING() {
    isStringMode = 2;
}

void ENDSTRING() {
    if (isCompileMode) {
        if (isStringMode == 1) compile("dostorestring");
        else if (isStringMode == 2) compile("doprintstring");
        char *string = (char *) pop(parameterStack);
        *user_code = (Dict *) (cell_t) string;
        user_code++;
        isStringMode = 0;
    } else if (isStringMode == 1) {
        isStringMode = 0;
    } else if (isStringMode == 2) {
        isStringMode = 0;
        char *stringPtr = (char *) pop(parameterStack);
        fprintf(stdout, "%s ", stringPtr);
    }
}

void TYPE() {
    char *stringPtr = (char *) pop(parameterStack);
    fprintf(stdout, "%s ", stringPtr);
}

void CONST(){
    char *token;
    int len = nextToken(&token);

    if (len >= MAX_WORD_NAME_SIZE) {
        WORD_SIZE_LIMIT(token);
        return;
    }

   addEntry(token, pop(parameterStack), NULL, &DOCONST);
}

void DOCONST(){
    push(parameterStack, wp->value);
}

void VAR(){
    char *token;
    int len = nextToken(&token);

    if (len >= MAX_WORD_NAME_SIZE) {
        WORD_SIZE_LIMIT(token);
        return;
    }

    int* ptr = malloc(sizeof(int));

    addEntry(token, (cell_t) ptr, NULL, &DOVAR);

}

void DOVAR(){
    push(parameterStack, wp->value);
}

void ASSIGNVAR(){
    cell_t * ptr = (cell_t*) pop(parameterStack);
    cell_t val = pop(parameterStack);

    *ptr = val;
}

void FETCHVAR(){
    cell_t* ptr = (cell_t*) pop(parameterStack);

    push(parameterStack, *ptr);
}

