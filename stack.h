#ifndef AMFORTH_STACK_H
#define AMFORTH_STACK_H


typedef struct Stack{
    int top;
    unsigned capacity;
    int* array;
} Stack;


Stack* createSack(unsigned capacity);

int isFull(Stack* stack);

int isEmpty(Stack* stack);

int push(Stack* stack, int item);

int pop(Stack* stack);

int peek(Stack* stack);

#endif //AMFORTH_STACK_H
