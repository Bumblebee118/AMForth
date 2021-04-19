//
// Created by Stefan Walser on 30.03.21.
//

#include "global.h"

int isCompileMode = 0; //init extern variable

void ADD() {
    cell_t a = pop(parameterStack);
    if (a == LONG_MIN) return;

    cell_t b = pop(parameterStack);
    if (b == LONG_MIN) return;

    cell_t sum = a + b;
    push(parameterStack, sum);
}

void SUBTRACT() {
    cell_t b = pop(parameterStack);
    if (b == LONG_MIN) return;

    cell_t a = pop(parameterStack);
    if (a == LONG_MIN) return;

    cell_t diff = a - b;
    push(parameterStack, diff);
}

void MULTIPLY() {
    cell_t a = pop(parameterStack);
    if (a == LONG_MIN) return;

    cell_t b = pop(parameterStack);
    if (b == LONG_MIN) return;

    cell_t sum = a * b;
    push(parameterStack, sum);
}

void DIVIDE() {
    cell_t b = pop(parameterStack);
    if (b == LONG_MIN) return;

    cell_t a = pop(parameterStack);
    if (a == LONG_MIN) return;

    int diff = a / b;
    push(parameterStack, diff);
}

void PRINTPOPSTACK() {
    cell_t a =  pop(parameterStack);
    if (a == LONG_MIN) return;

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

void DOCOLON(){
    //TODO repair
    push(returnStack, (cell_t) ip);
    ip = wp->definitions;
}

void COLON() {
    char* word;
    int len = nextToken(&word);

    if(len >= MAX_WORD_NAME_SIZE){
        //ZERO_LEN();
        WORD_SIZE_LIMIT();
        return;
    }

    addEntry(word, 0, NULL, user_code, &DOCOLON);
    compile("docol");

    isCompileMode = 1;
}

void DOSEMI(){
    ip = (Dict**)pop(returnStack);
}

void SEMI(){
    compile("dosemi");
    isCompileMode = 0;
}

void NEXT(){
}

void INTERPRET(){
    interpret();
}

void EXECUTE(){
    char** word = (char**) pop(parameterStack);
    push(parameterStack, execute(*word));
}

void BRANCH0(){
    cell_t val = pop(parameterStack);
    //if(val == 0){
        ip = ip-3;
    //}
}

