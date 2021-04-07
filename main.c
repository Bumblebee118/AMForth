#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dict.h"
#include "interpret.h"

void printSynopsis(void);
void tests(Dict *dict, Stack *stack);


int main(int argc, char **argv) {

    //initialize stacks and dictionary
    Dict *dict = createDict();
    Stack *parameterStack = createStack(STANDARD_STACK_CAPACITY);
    Stack *returnStack = createStack(STANDARD_STACK_CAPACITY);

    //TODO automatically fill the dictionary with the basic functions

    tests(dict, parameterStack);

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
            exit(EXIT_FAILURE);
        }
    }

    startInterpret(inputStream, dict, parameterStack, returnStack);

    deleteDict(dict);
    deleteStack(parameterStack);
    deleteStack(returnStack);

    exit(EXIT_SUCCESS);
}

void printSynopsis(void) {
    fprintf(stdout, "Usage: ./forth [FILE]\n");
}


void tests(Dict *dict, Stack *stack) {
    push(stack, 10);
    push(stack, 2100);
    push(stack, -1);
    push(stack, 13);
   // printf("%d\n", peek(stack));

//    printf("%d popped from stack\n", pop(stack));
//    printf("%d popped from stack\n", pop(stack));
//    printf("%d popped from stack\n", pop(stack));

    addEntry(dict, "+", 0, NULL, NULL, &ADD);
    addEntry(dict, "-", 0, NULL, NULL, &SUBTRACT);
    addEntry(dict, "*", 0, NULL, NULL, &MULTIPLY);
    addEntry(dict, "/", 0, NULL, NULL, &DIVIDE);
    addEntry(dict, ".", 0, NULL, NULL, &PRINTPOPSTACK);
    addEntry(dict, ".s", 0, NULL, NULL, &PRINTSTACK);
    addEntry(dict, ";", 0, NULL, NULL, NULL);
    DictEntry **entries = (DictEntry **) malloc(3 * sizeof(DictEntry *));
    entries[0] = getEntry(dict, "+");
    entries[1] = getEntry(dict, "-");
    entries[2] = getEntry(dict, ";");
    addEntry(dict, "addsub", 0, NULL, entries, NULL);

    getEntry(dict, "+")->basicfunc(stack);

    //printf("%d\n", peek(stack));

    getEntry(dict, "-")->basicfunc(stack);

  //  printf("%d\n", peek(stack));


    /*removeEntry(dict, "add");

    if (getEntry(dict, "add")==NULL){
        printf("Yep this is Null!\n");
    }

    getEntry(dict, "sub")->basicfunc(stack);

    printf("%d\n", peek(stack));*/

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
