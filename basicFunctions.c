//
// Created by Stefan Walser on 30.03.21.
//

#include <stdio.h>
#include "basicFunctions.h"
#include "error.h"

int ADD(Stack *stack) {
    int a = pop(stack);
    int b = pop(stack);
    int sum = a + b;
    push(stack, sum);
    return 0;
}

int SUBTRACT(Stack *stack) {
    int b = pop(stack);
    int a = pop(stack);
    int diff = a - b;
    push(stack, diff);
    return 0;
}

int MULTIPLY(Stack *stack) {
    int a = pop(stack);
    int b = pop(stack);
    int sum = a * b;
    push(stack, sum);
    return 0;
}

int DIVIDE(Stack *stack) {
    int b = pop(stack);
    int a = pop(stack);
    int diff = a / b;
    push(stack, diff);
    return 0;
}

int PRINTPOPSTACK(Stack *stack){
    if (isEmpty(stack) == 0){
        fprintf(stdout," %d", pop(stack));
        return 0;
    }else{
        PRINT_ERROR_MSG("Stack underflow", ".");
        clearStack(stack);
        return -1;
    }

}

int PRINTSTACK(Stack *stack){

    fprintf(stdout, " <%d>", (stack->top)+1);

    int i = 0;
    while (i <= stack->top){
        fprintf(stdout," %d", stack->array[i]);
        i++;
    }

    return 0;
}