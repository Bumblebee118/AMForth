//
// Created by Stefan Walser on 30.03.21.
//

#include <stdio.h>
#include <zconf.h>
#include "basicFunctions.h"

int ADD(Stack *stack) {
    int a = pop(stack);
    if (a == INT_MIN) return -1;

    int b = pop(stack);
    if (b == INT_MIN) return -1;

    int sum = a + b;
    push(stack, sum);
    return 0;
}

int SUBTRACT(Stack *stack) {
    int b = pop(stack);
    if (b == INT_MIN) return -1;

    int a = pop(stack);
    if (a == INT_MIN) return -1;

    int diff = a - b;
    push(stack, diff);
    return 0;
}

int MULTIPLY(Stack *stack) {
    int a = pop(stack);
    if (a == INT_MIN) return -1;

    int b = pop(stack);
    if (b == INT_MIN) return -1;

    int sum = a * b;
    push(stack, sum);
    return 0;
}

int DIVIDE(Stack *stack) {
    int b = pop(stack);
    if (b == INT_MIN) return -1;

    int a = pop(stack);
    if (a == INT_MIN) return -1;

    int diff = a / b;
    push(stack, diff);
    return 0;
}

int PRINTPOPSTACK(Stack *stack) {
    int a =  pop(stack);
    if (a == INT_MIN) return -1;

    fprintf(stdout, " %d", a);
    return 0;
}

int PRINTSTACK(Stack *stack) {

    fprintf(stdout, " <%d>", (stack->top) + 1);

    int i = 0;
    while (i <= stack->top) {
        fprintf(stdout, " %d", stack->array[i]);
        i++;
    }

    return 0;
}