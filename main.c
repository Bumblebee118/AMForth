#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dict.h"

int main() {

    Stack* stack = createSack(128);

    push(stack, 10);
    push(stack, 2100);
    push(stack,-1);
    push(stack, 13);

    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));
    printf("%d popped from stack\n", pop(stack));

    Dict* dict = createDict();
    addEntry(dict, "test1", 4);
    addEntry(dict, "test2", 8);
    addEntry(dict, "test3", 12);

    printf("%s was found in the dictionary\n", searchEntry(dict, "test2")->functionName);
    printf("%s was found in the dictionary\n", searchEntry(dict, "test1")->functionName);
    printf("%s was found in the dictionary\n", searchEntry(dict, "test3")->functionName);

    exit(EXIT_SUCCESS);
}
