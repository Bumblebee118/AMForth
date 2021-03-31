//
// Created by Stefan Walser on 30.03.21.
//

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