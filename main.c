#include <stdio.h>
#include "stack.h"

int main() {

    Stack* stack = createSack(128);

    push(stack, 10);
    push(stack, 2100);
    push(stack,-1);
    push(stack, 13);

    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));
    return 0;
}
