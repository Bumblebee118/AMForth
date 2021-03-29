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
    addEntry(dict, "test1", 13);

    DictEntry* d = searchEntry(dict, "test2");
    printf("%s was found in the dictionary with address %d\n", d->functionName, d->functionAddress);
    d = searchEntry(dict, "test1");
    printf("%s was found in the dictionary with address %d\n", d->functionName, d->functionAddress);
    d = searchEntry(dict, "test3");
    printf("%s was found in the dictionary with address %d\n", d->functionName, d->functionAddress);

    exit(EXIT_SUCCESS);
}
