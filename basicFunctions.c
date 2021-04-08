//
// Created by Stefan Walser on 30.03.21.
//

#include "global.h"

int inCompileMode = 0;

int ADD() {
    int a = pop(parameterStack);
    if (a == INT_MIN) return -1;

    int b = pop(parameterStack);
    if (b == INT_MIN) return -1;

    int sum = a + b;
    push(parameterStack, sum);
    return 0;
}

int SUBTRACT() {
    int b = pop(parameterStack);
    if (b == INT_MIN) return -1;

    int a = pop(parameterStack);
    if (a == INT_MIN) return -1;

    int diff = a - b;
    push(parameterStack, diff);
    return 0;
}

int MULTIPLY() {
    int a = pop(parameterStack);
    if (a == INT_MIN) return -1;

    int b = pop(parameterStack);
    if (b == INT_MIN) return -1;

    int sum = a * b;
    push(parameterStack, sum);
    return 0;
}

int DIVIDE() {
    int b = pop(parameterStack);
    if (b == INT_MIN) return -1;

    int a = pop(parameterStack);
    if (a == INT_MIN) return -1;

    int diff = a / b;
    push(parameterStack, diff);
    return 0;
}

int PRINTPOPSTACK() {
    int a =  pop(parameterStack);
    if (a == INT_MIN) return -1;

    fprintf(stdout, " %d", a);
    return 0;
}

int PRINTSTACK() {

    fprintf(stdout, " <%d>", (parameterStack->top) + 1);

    int i = 0;
    while (i <= parameterStack->top) {
        fprintf(stdout, " %d", parameterStack->array[i]);
        i++;
    }

    return 0;
}

int DOCOLON() {
    inCompileMode = 1;
    return 0;
}