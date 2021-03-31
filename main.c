#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dict.h"
#include "textint.h"
#include "basicFunctions.h"

void printSynopsis(void);

void tests(Dict *dict, Stack *stack, FunctionPool *functionPool);

void addBasicFunctions(Dict *dict);

int main(int argc, char **argv) {

    Dict *dict = createDict();
    Stack *stack = createStack(128);
    FunctionPool *functionPool = createFunctionPool(128);

    tests(dict, stack, functionPool);

    addBasicFunctions(dict);

    if (argc > 2) {
        printSynopsis();
        exit(EXIT_FAILURE);
    }
    FILE *inputStream = stdin;

    if (argc > 1) {
        char *filename = argv[1];
        inputStream = fopen(filename, "r");

        if (inputStream == NULL) {
            printSynopsis();
        }
    }

    startTextInterpreter(inputStream);

    deleteDict(dict);
    deleteFunctionPool(functionPool);
    exit(EXIT_SUCCESS);
}

void printSynopsis(void) {
    fprintf(stdin, "Usage: ./forth [FILE]");
}


void tests(Dict *dict, Stack *stack, FunctionPool *functionPool) {
    push(stack, 10);
    push(stack, 2100);
    push(stack, -1);
    push(stack, 13);
    printf("%d\n", peek(stack));

//    printf("%d popped from stack\n", pop(stack));
//    printf("%d popped from stack\n", pop(stack));
//    printf("%d popped from stack\n", pop(stack));

    addWordToPool(dict, "add", functionPool, &ADD);
    addWordToPool(dict, "subtract", functionPool, &SUBTRACT);

    getWordFromPool(dict, functionPool, "add")(stack);

    printf("%d\n", peek(stack));

//    addEntry(dict, "test1", 4);
//    addEntry(dict, "test2", 8);
//    addEntry(dict, "test3", 12);
//    addEntry(dict, "test1", 13);

//    DictEntry *d = searchEntry(dict, "test2");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(dict, "test1");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    d = searchEntry(dict, "test3");
//    printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//
//    int r = removeEntry(dict, "test1");
//    printf("%d was returned from the delete function\n", r);
//    r = removeEntry(dict, "test1");
//    printf("%d was returned from the delete function\n", r);
//
//    d = searchEntry(dict, "test1");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//
//    d = searchEntry(dict, "test2");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
//    d = searchEntry(dict, "test3");
//    if (d != NULL) {
//        printf("%s was found in the dictionary with address %d\n", d->word, d->functionAddress);
//    } else {
//        printf("This element was not found in the list.\n");
//    }
}

void addBasicFunctions(Dict *dict) {
    addEntry(dict, "add", 0);
}
