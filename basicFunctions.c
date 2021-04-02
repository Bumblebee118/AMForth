//
// Created by Stefan Walser on 30.03.21.
//

#include <stdio.h>
#include "basicFunctions.h"

void ADD(Stack *stack) {
    int a = pop(stack);
    int b = pop(stack);
    int sum = a + b;
    push(stack, sum);
}

void SUBTRACT(Stack *stack) {
    int b = pop(stack);
    int a = pop(stack);
    int diff = a - b;
    push(stack, diff);
}

void MULTIPLY(Stack *stack) {
    int a = pop(stack);
    int b = pop(stack);
    int sum = a * b;
    push(stack, sum);
}

void DIVIDE(Stack *stack) {
    int b = pop(stack);
    int a = pop(stack);
    int diff = a / b;
    push(stack, diff);
}

void PRINTPOPSTACK(Stack *stack){
    if (isEmpty(stack) != 0){
        printf("%d", pop(stack));
    }else{
        printf("Stack underflow\n");
        clearStack(stack);
    }

}

void PRINTSTACK(Stack *stack){

    printf(" <%d>", (stack->top)+1);

    int i = 0;
    while (i <= stack->top){
        printf(" %d", stack->array[i]);
        i++;
    }
}