#ifndef AMFORTH_STACK_H
#define AMFORTH_STACK_H

//Struct to create a stack
//'top' points to the last element in the array 'array'
//capacity defines the size of 'array'
typedef struct Stack{
    int top;
    unsigned capacity;
    int* array;
} Stack;

//mallocs memory for a new stack Struct with the given capacity
Stack* createSack(unsigned capacity);

//retruns true if the stack is full
int isFull(Stack* stack);

//returns true if the stack is empty
int isEmpty(Stack* stack);

//pushes the element 'item' on the top of the stack
int push(Stack* stack, int item);

//pops the last element of the stack
int pop(Stack* stack);

//looks at the last element of the stack without modifying the stack
int peek(Stack* stack);

#endif //AMFORTH_STACK_H
